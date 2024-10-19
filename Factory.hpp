#pragma once

#include <vector>

#include "Product.hpp"

class Factory
{

private:

    int ProductsPerHour = 0;
    char FactoryName = '?';
    char ProductName = '?';
    int ProductWeight = 0;
    WrapperType ProductWrapper = WrapperType::Cardboard;

public:

    const char GetFactoryName() const
    {
        return FactoryName;
    }

    const int GetProductsPerHour() const
    {
        return ProductsPerHour;
    }

    const int GetProductsWeight() const
    {
        return ProductWeight;
    }

    Factory& operator=(const Factory&) = delete;
    Factory(const Factory&) = delete;
    Factory() = delete;

    Factory(int NewProductsPerHour, char NewFactoryName, char NewProductName, int NewProductWeight, WrapperType NewWrapperType) :
        ProductsPerHour(NewProductsPerHour), FactoryName(NewFactoryName), ProductName(NewProductName), ProductWeight(NewProductWeight),
        ProductWrapper(NewWrapperType)
    {

    }

    friend std::ostream& operator<<(std::ostream& os, const Factory& factory)
    {
        os << "Name: " << factory.FactoryName << " Products per hour: " << factory.ProductsPerHour << " Product name: " << factory.ProductName <<
            " Product weight: " << factory.ProductWeight << " Product wrapper: " << factory.ProductWrapper;
        return os;
    }

    void Produce(std::vector<Product>& Result) const
    {
        for (int i = 0; i < ProductsPerHour; ++i)
        {
            Product NewProduct;
            NewProduct.Name = ProductName;
            NewProduct.Weight = ProductWeight;
            NewProduct.Wrapper = ProductWrapper;
            Result.push_back(NewProduct);
        }
    }
};
