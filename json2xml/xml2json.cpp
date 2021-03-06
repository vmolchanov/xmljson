#include "xml2json.h"

static bool xml2json_has_digits_only(const char *input, bool *hasDecimal) {
    if (input == nullptr) {
        return false;
    }

    const char *runPtr = input;

    *hasDecimal = false;

    while (*runPtr != '\0') {
        if (*runPtr == '.') {
            if (!(*hasDecimal)) {
                *hasDecimal = true;
            } else {
                return false;
            }
        } else if (isalpha(*runPtr)) {
            return false;
        }
        runPtr++;
    }

    return true;
}

void xml2json_to_array_form(
    const char *name,
    rapidjson::Value &jsvalue,
    rapidjson::Value &jsvalue_chd,
    rapidjson::Document::AllocatorType& allocator
) {
    rapidjson::Value jsvalue_target;
    rapidjson::Value jn;

    jn.SetString(name, allocator);
    jsvalue_target = jsvalue.FindMember(name)->value;

    if (jsvalue_target.IsArray()) {
        jsvalue_target.PushBack(jsvalue_chd, allocator);
        jsvalue.RemoveMember(name);
        jsvalue.AddMember(jn, jsvalue_target, allocator);
    } else {
        rapidjson::Value jsvalue_array;
        jsvalue_array.SetArray();
        jsvalue_array.PushBack(jsvalue_target, allocator);
        jsvalue_array.PushBack(jsvalue_chd, allocator);
        jsvalue.RemoveMember(name);
        jsvalue.AddMember(jn, jsvalue_array, allocator);
    }
}

void xml2json_add_attributes(
    rapidxml::xml_node<> *xmlnode,
    rapidjson::Value &jsvalue,
    rapidjson::Document::AllocatorType& allocator
) {
    rapidxml::xml_attribute<> *myattr;

    for (myattr = xmlnode->first_attribute(); myattr; myattr = myattr->next_attribute()) {
        rapidjson::Value jn, jv;

        jn.SetString((std::string(xml2json_attribute_name_prefix) + myattr->name()).c_str(), allocator);

        if (xml2json_numeric_support == false) {
            jv.SetString(myattr->value(), allocator);
        } else {
            bool hasDecimal;
            if (xml2json_has_digits_only(myattr->value(), &hasDecimal) == false) {
                jv.SetString(myattr->value(), allocator);
            } else {
                if (hasDecimal) {
                    double value = std::strtod(myattr->value(),nullptr);
                    jv.SetDouble(value);
                } else {
                    long int value = std::strtol(myattr->value(), nullptr, 0);
                    jv.SetInt(value);
                }
            }
        }
        jsvalue.AddMember(jn, jv, allocator);
    }
}

void xml2json_traverse_node(
    rapidxml::xml_node<> *xmlnode,
    rapidjson::Value &jsvalue,
    rapidjson::Document::AllocatorType& allocator
) {
    rapidjson::Value jsvalue_chd;

    jsvalue.SetObject();
    jsvalue_chd.SetObject();

    rapidxml::xml_node<> *xmlnode_chd;

    if ((xmlnode->type() == rapidxml::node_data || xmlnode->type() == rapidxml::node_cdata) && xmlnode->value()) {
        jsvalue.SetString(xmlnode->value(), allocator);
    } else if (xmlnode->type() == rapidxml::node_element) {
        if (xmlnode->first_attribute()) {
            if (xmlnode->first_node() && xmlnode->first_node()->type() == rapidxml::node_data && count_children(xmlnode) == 1) {
                rapidjson::Value jn, jv;
                jn.SetString(xml2json_text_additional_name, allocator);
                jv.SetString(xmlnode->first_node()->value(), allocator);
                jsvalue.AddMember(jn, jv, allocator);
                xml2json_add_attributes(xmlnode, jsvalue, allocator);
                return;
            } else {
                xml2json_add_attributes(xmlnode, jsvalue, allocator);
            }
        } else {
            if (!xmlnode->first_node()) {
                jsvalue.SetNull();
                return;
            } else if (xmlnode->first_node()->type() == rapidxml::node_data && count_children(xmlnode) == 1) {
                if (xml2json_numeric_support == false) {
                    jsvalue.SetString(rapidjson::StringRef(xmlnode->first_node()->value()), allocator);
                } else {
                    bool hasDecimal;
                    if (xml2json_has_digits_only(xmlnode->first_node()->value(), &hasDecimal) == false) {
                        jsvalue.SetString(rapidjson::StringRef(xmlnode->first_node()->value()), allocator);
                    } else {
                        if (hasDecimal) {
                            double value = std::strtod(xmlnode->first_node()->value(), nullptr);
                            jsvalue.SetDouble(value);
                        } else {
                            long int value = std::strtol(xmlnode->first_node()->value(), nullptr, 0);
                            jsvalue.SetInt(value);
                        }
                    }
                }
                return;
            }
        }

        if (xmlnode->first_node()) {
            std::map<std::string, int> name_count;

            for (xmlnode_chd = xmlnode->first_node(); xmlnode_chd; xmlnode_chd = xmlnode_chd->next_sibling()) {
                std::string current_name;
                const char *name_ptr = NULL;
                rapidjson::Value jn, jv;

                if (xmlnode_chd->type() == rapidxml::node_data || xmlnode_chd->type() == rapidxml::node_cdata) {
                    current_name = xml2json_text_additional_name;
                    name_count[current_name]++;
                    jv.SetString(xml2json_text_additional_name, allocator);
                    name_ptr = jv.GetString();
                } else if (xmlnode_chd->type() == rapidxml::node_element) {
                    current_name = xmlnode_chd->name();
                    name_count[current_name]++;
                    name_ptr = xmlnode_chd->name();
                }

                xml2json_traverse_node(xmlnode_chd, jsvalue_chd, allocator);

                if (name_count[current_name] > 1 && name_ptr)
                    xml2json_to_array_form(name_ptr, jsvalue, jsvalue_chd, allocator);
                else {
                    jn.SetString(name_ptr, allocator);
                    jsvalue.AddMember(jn, jsvalue_chd, allocator);
                }
            }
        }
    } else {
        std::cerr << "err data!!" << std::endl;
    }
}

std::string xml2json(const char *xml_str) {
    rapidxml::xml_document<> *xml_doc = new rapidxml::xml_document<>();
    xml_doc->parse<0> (const_cast<char *>(xml_str));

    rapidjson::Document js_doc;
    js_doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = js_doc.GetAllocator();

    rapidxml::xml_node<> *xmlnode_chd;

    for (xmlnode_chd = xml_doc->first_node(); xmlnode_chd; xmlnode_chd = xmlnode_chd->next_sibling()) {
        rapidjson::Value jsvalue_chd;
        jsvalue_chd.SetObject();
        xml2json_traverse_node(xmlnode_chd, jsvalue_chd, allocator);
        js_doc.AddMember(rapidjson::StringRef(xmlnode_chd->name()), jsvalue_chd, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    js_doc.Accept(writer);
    delete xml_doc;
    return buffer.GetString();
}
