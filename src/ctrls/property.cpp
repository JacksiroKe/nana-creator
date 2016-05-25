/*
 *		ctrls::property Implementation
 *
 *      Nana C++ Library - Creator
 *      Author: besh81
 */

#include <iostream>
#include <assert.h>
#include "ctrls/property.h"


namespace ctrls
{
	namespace impl
	{
		inline bool get_as_bool(const std::string& value)
		{
			// only look at first char
			char first = value[0];
			// 1*, t* (true), T* (True), y* (yes), Y* (YES)
			return (first == '1' || first == 't' || first == 'T' || first == 'y' || first == 'Y');
		}
	}//end namespace impl


	property_proxy& property_proxy::name(const std::string& name)
	{
		_prop->name = name;
		return *this;
	}
	std::string property_proxy::name() const
	{
		return _prop->name;
	}

	property_proxy& property_proxy::value(const std::string& value)
	{
		_prop->value = value;
		return *this;
	}
	std::string property_proxy::value() const
	{
		return _prop->value;
	}

	property_proxy& property_proxy::label(const std::string& label)
	{
		_prop->label = label;
		return *this;
	}
	std::string property_proxy::label() const
	{
		return _prop->label;
	}

	property_proxy& property_proxy::category(const std::string& category)
	{
		_prop->category = category;
		return *this;
	}
	std::string property_proxy::category() const
	{
		return _prop->category;
	}

	property_proxy& property_proxy::type(const pg_type type)
	{
		_prop->type = type;
		return *this;
	}
	pg_type property_proxy::type() const
	{
		return _prop->type;
	}

	property_proxy& property_proxy::type_hints(const nana::any hints)
	{
		_prop->type_hints = hints;
		return *this;
	}
	nana::any property_proxy::type_hints() const
	{
		return _prop->type_hints;
	}



	bool property_proxy::operator==(const property_proxy& r) const
	{
		return (_prop == r._prop);
	}
	bool property_proxy::operator!=(const property_proxy& r) const
	{
		return (_prop != r._prop);
	}



	const std::string& property_proxy::as_string(const std::string& def) const
	{
		return !_prop ? def : (!_prop->value.empty() ? _prop->value : def);
	}
	int property_proxy::as_int(int def) const
	{
		return !_prop ? def : (!_prop->value.empty() ? std::stoi(_prop->value) : def);
	}
	unsigned int property_proxy::as_uint(unsigned int def) const
	{
		return !_prop ? def : (!_prop->value.empty() ? std::stoul(_prop->value) : def);
	}
	double property_proxy::as_double(double def) const
	{
		return !_prop ? def : (!_prop->value.empty() ? std::stod(_prop->value) : def);
	}
	float property_proxy::as_float(float def) const
	{
		return !_prop ? def : (!_prop->value.empty() ? std::stof(_prop->value) : def);
	}
	bool property_proxy::as_bool(bool def) const
	{
		return !_prop ? def : (!_prop->value.empty() ? impl::get_as_bool(_prop->value) : def);
	}



	property_proxy& property_proxy::value(const char* value)
	{
		_prop->value = value;
		return *this;
	}
	property_proxy& property_proxy::value(int value)
	{
		_prop->value = std::to_string(value);
		return *this;
	}

	property_proxy& property_proxy::value(unsigned int value)
	{
		_prop->value = std::to_string(value);
		return *this;
	}

	property_proxy& property_proxy::value(double value)
	{
		_prop->value = std::to_string(value);
		return *this;
	}

	property_proxy& property_proxy::value(float value)
	{
		_prop->value = std::to_string(value);
		return *this;
	}

	property_proxy& property_proxy::value(bool value)
	{
		_prop->value = value ? "true" : "false";
		return *this;
	}


	property_proxy& property_proxy::operator=(const std::string& value_)
	{
		value(value_);
		return *this;
	}
	property_proxy& property_proxy::operator=(const char* value_)
	{
		value(value_);
		return *this;
	}
	property_proxy& property_proxy::operator=(int value_)
	{
		value(value_);
		return *this;
	}
	property_proxy& property_proxy::operator=(unsigned int value_)
	{
		value(value_);
		return *this;
	}
	property_proxy& property_proxy::operator=(double value_)
	{
		value(value_);
		return *this;
	}
	property_proxy& property_proxy::operator=(float value_)
	{
		value(value_);
		return *this;
	}
	property_proxy& property_proxy::operator=(bool value_)
	{
		value(value_);
		return *this;
	}

	property_t* property_proxy::_m_prop() const
	{
		return _prop;
	}



	properties_collection::~properties_collection()
	{
		_props.clear();
	}


	bool properties_collection::empty() const
	{
		return _props.empty();
	}

	property_proxy properties_collection::append(const std::string& name)
	{
		property_t prop;
		prop.name = name;
		_props.push_back(prop);
		return property_proxy{ &_props.back() };
	}
	property_proxy properties_collection::append(const property_t& prop)
	{
		_props.push_back(prop);
		return property_proxy{ &_props.back() };
	}

	property_proxy properties_collection::property(const std::string& name)
	{
		for(auto i = _props.begin(); i < _props.end(); ++i)
			if(i->name == name)
				return property_proxy{ &*i };

		return property_proxy{};
	}
	
	size_t properties_collection::count() const
	{
		return _props.size();
	}

	property_proxy properties_collection::operator[](size_t index)
	{
		assert(index < _props.size());
		return property_proxy{ &_props[index] };
	}


	/*property_proxy properties_collection::first() const
	{
		return _props.begin();
	}

	/*property_proxy properties_collection::last() const
	{
		return _first_attribute ? property_proxy(_first_attribute->prev_attribute) : property_proxy();
	}

	property_proxy properties_collection::attribute(const std::string& name) const
	{
		for(auto i = _first_attribute; i; i = i->next_attribute)
			if(i->name.compare(name) == 0)
				return property_proxy(i);

		return property_proxy();
	}

	property_proxy properties_collection::append(const std::string& name)
	{
		attribute_struct* attr = new attribute_struct();

		impl::append_attribute(attr, &_first_attribute);

		property_proxy a(attr);
		a.set_name(name);
		return a;
	}

	property_proxy properties_collection::prepend(const std::string& name)
	{
		attribute_struct* attr = new attribute_struct();

		impl::prepend_attribute(attr, &_first_attribute);

		property_proxy a(attr);
		a.set_name(name);
		return a;
	}

	property_proxy properties_collection::insert_after(const std::string& name, const property_proxy& attr_)
	{
		attribute_struct* attr = new attribute_struct();

		impl::insert_attribute_after(attr, attr_.internal_object(), &_first_attribute);

		property_proxy a(attr);
		a.set_name(name);
		return a;
	}

	property_proxy properties_collection::insert_before(const std::string& name, const property_proxy& attr_)
	{
		attribute_struct* attr = new attribute_struct();

		impl::insert_attribute_before(attr, attr_.internal_object(), &_first_attribute);

		property_proxy a(attr);
		a.set_name(name);
		return a;
	}

	property_proxy properties_collection::append_copy(const property_proxy& proto)
	{
		attribute_struct* attr = new attribute_struct();

		impl::append_attribute(attr, &_first_attribute);

		property_proxy a(attr);
		a.set_name(proto.name());
		a.set_value(proto.value());
		return a;
	}

	property_proxy properties_collection::prepend_copy(const property_proxy& proto)
	{
		attribute_struct* attr = new attribute_struct();

		impl::prepend_attribute(attr, &_first_attribute);

		property_proxy a(attr);
		a.set_name(proto.name());
		a.set_value(proto.value());
		return a;
	}

	property_proxy properties_collection::insert_copy_after(const property_proxy& proto, const property_proxy& attr_)
	{
		attribute_struct* attr = new attribute_struct();

		impl::insert_attribute_after(attr, attr_.internal_object(), &_first_attribute);

		property_proxy a(attr);
		a.set_name(proto.name());
		a.set_value(proto.value());
		return a;
	}

	property_proxy properties_collection::insert_copy_before(const property_proxy& proto, const property_proxy& attr_)
	{
		attribute_struct* attr = new attribute_struct();

		impl::insert_attribute_before(attr, attr_.internal_object(), &_first_attribute);

		property_proxy a(attr);
		a.set_name(proto.name());
		a.set_value(proto.value());
		return a;
	}


	bool properties_collection::remove(const std::string& name)
	{
		return remove(attribute(name));
	}


	bool properties_collection::remove(const property_proxy& a)
	{
		impl::remove_attribute(a.internal_object(), &_first_attribute);
		impl::destroy_attribute(a.internal_object());

		return true;
	}
	*/

}//end namespace ctrls