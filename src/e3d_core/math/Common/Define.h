#pragma once

#include <memory>


namespace E3dMath {

#define NEW_AS_UNIQUE_PTR(TYPE, ...) std::unique_ptr<TYPE>(new TYPE(__VA_ARGS__))
#define NEW_AS_SHARED_PTR(TYPE, ...) std::shared_ptr<TYPE>(new TYPE(__VA_ARGS__))

    template<class Derived, class Base>
    inline
    std::unique_ptr<Derived> TransferOwnershipCast(std::unique_ptr<Base> &obj) {
        const Derived *pDerived = dynamic_cast<const Derived *>(obj.get());
        if (!pDerived) {
            return nullptr;
        }
        return std::unique_ptr<Derived>(dynamic_cast<Derived *>(obj.release()));
    }

    template<class Derived, class Base>
    inline
    std::unique_ptr<Derived> TransferOwnershipCast(std::unique_ptr<Base> &&obj) {
        const Derived *pDerived = dynamic_cast<const Derived *>(obj.get());
        if (!pDerived) {
            return nullptr;
        }
        return std::unique_ptr<Derived>(dynamic_cast<Derived *>(obj.release()));
    }

}





