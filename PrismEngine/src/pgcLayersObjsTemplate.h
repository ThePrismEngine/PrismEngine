#pragma once
#include "utils.h"
#include "layersMacroses.h"


DECLARE_PGC_LAYER_INSTANCE(L1)

template<typename Derived>
class L1_Object {
public:
	L1_Object() : context(nullptr), settings(nullptr) {}
	void init(PGC::utils::Context* context, PGC::utils::Settings* settings) {
		this->context = context;
		this->settings = settings;
		derived().createImpl();
	};

	void cleanup() {
		if (isInitialized()) {
			derived().cleanupImpl();
			context = nullptr;
			settings = nullptr;
		}
	}

	virtual ~L1_Object() {
		cleanup();
	}

	PGC::utils::Context* getContext() const { return context; }
	PGC::utils::Settings* getSettings() const { return settings; }
	bool isInitialized() const { return context != nullptr && settings != nullptr; }
protected:
	PGC::utils::Context* context;
	PGC::utils::Settings* settings;

private:
	Derived& derived() {
		return *static_cast<Derived*>(this);
	}

	const Derived& derived() const {
		return *static_cast<const Derived*>(this);
	}
};

END_NAMESPACE_DECLARATION

DECLARE_PGC_LAYER_INSTANCE(L2)

template<typename Derived>
class L2_Object {
public:
	L2_Object(PGC::utils::Context* context, PGC::utils::Settings* settings) : context(context), settings(settings) { createImpl(); }

	void cleanup() {
		if (isInitialized()) {
			derived().cleanupImpl();
			context = nullptr;
			settings = nullptr;
		}
	}

	void createImpl() {};
	void cleanupImpl() {};

	virtual ~L2_Object() {
		cleanup();
	}

	PGC::utils::Context* getContext() const { return context; }
	PGC::utils::Settings* getSettings() const { return settings; }
	bool isInitialized() const { return context != nullptr && settings != nullptr; }
protected:
	PGC::utils::Context* context;
	PGC::utils::Settings* settings;

private:
	Derived& derived() {
		return *static_cast<Derived*>(this);
	}

	const Derived& derived() const {
		return *static_cast<const Derived*>(this);
	}
};

END_NAMESPACE_DECLARATION