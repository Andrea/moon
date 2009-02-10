/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * provider.h: an api for PropertyValue providers (for property inheritance)
 *
 * Copyright 2007 Novell, Inc. (http://www.novell.com)
 *
 * See the LICENSE file included with the distribution for details.
 * 
 */

#ifndef __MOON_PROVIDER_H__
#define __MOON_PROVIDER_H__

#include <glib.h>

class DependencyObject;
class DependencyProperty;
class Surface;
class Style;
struct Value;

enum PropertyPrecedence {
	PropertyPrecedence_Animation,
	PropertyPrecedence_LocalValue,
	PropertyPrecedence_DynamicValue, // use this level for types that need to compute property values lazily
	PropertyPrecedence_Style,
	PropertyPrecedence_Inherited,
	PropertyPrecedence_DefaultValue,
	PropertyPrecedence_AutoCreate,

	PropertyPrecedence_Count,

	PropertyPrecedence_Highest = PropertyPrecedence_Animation
};

class PropertyValueProvider {
public:
	PropertyValueProvider (DependencyObject *_obj) : obj(_obj) { }
	virtual ~PropertyValueProvider () { }

	virtual Value *GetPropertyValue (DependencyProperty *property) = 0;

	virtual void RecomputePropertyValue (DependencyProperty *property) { }

protected:
	DependencyObject *obj;
};


class AnimationPropertyValueProvider : public PropertyValueProvider {
public:
	AnimationPropertyValueProvider (DependencyObject *obj) : PropertyValueProvider (obj) { };
	virtual ~AnimationPropertyValueProvider () { };

	virtual Value *GetPropertyValue (DependencyProperty *property);
};

class LocalPropertyValueProvider : public PropertyValueProvider {
public:
	LocalPropertyValueProvider (DependencyObject *obj);
	virtual ~LocalPropertyValueProvider ();

	virtual Value *GetPropertyValue (DependencyProperty *property);
};

class StylePropertyValueProvider : public PropertyValueProvider {
public:
	StylePropertyValueProvider (DependencyObject *obj);
	virtual ~StylePropertyValueProvider ();

	virtual Value *GetPropertyValue (DependencyProperty *property);

	virtual void RecomputePropertyValue (DependencyProperty *property);

	void SealStyle (Style *style);

private:
	GHashTable *style_hash;
};

class InheritedPropertyValueProvider : public PropertyValueProvider {
public:
	InheritedPropertyValueProvider (DependencyObject *obj) : PropertyValueProvider (obj) { };
	virtual ~InheritedPropertyValueProvider () { };

	virtual Value *GetPropertyValue (DependencyProperty *property);
};

class DefaultValuePropertyValueProvider : public PropertyValueProvider {
public:
	DefaultValuePropertyValueProvider (DependencyObject *obj) : PropertyValueProvider (obj) { };
	virtual ~DefaultValuePropertyValueProvider () { };

	virtual Value *GetPropertyValue (DependencyProperty *property);
};

class AutoCreatePropertyValueProvider : public PropertyValueProvider {
	GHashTable *auto_values;
	
 public:
	AutoCreatePropertyValueProvider (DependencyObject *obj);
	virtual ~AutoCreatePropertyValueProvider ();

	virtual Value *GetPropertyValue (DependencyProperty *property);
	
	Value *ReadLocalValue (DependencyProperty *property);
	void ClearValue (DependencyProperty *property);
	void SetSurface (Surface *surface);
};


#endif /* __MOON_PROVIDER_H__ */
