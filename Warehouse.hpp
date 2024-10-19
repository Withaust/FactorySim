#pragma once

#include <vector>

#include "Product.hpp"
#include "VehicleManager.hpp"

class Warehouse
{
private:

    int Capacity = 0;
    std::vector<Product> Stored;

public:

    const size_t GetStoredCount() const
    {
        return Stored.size();
    }

    Warehouse& operator=(const Warehouse&) = delete;
    Warehouse() = delete;

    Warehouse(int NewCapacity) : Capacity(NewCapacity)
    {
        Stored.reserve(Capacity);
    }

    void FillStorage(std::vector<Product>& NewProducts)
    {
        for (const auto& Product : NewProducts)
        {
            if (Stored.size() >= Capacity)
            {
                std::cout << "Warehouse overflowed!\n";
                break;
            }
            Stored.push_back(Product);
        }
    }

    bool IsCloseToFull()
    {
        return ((Stored.size() * 100) / Capacity) > 95.0f;
    }

    void DispatchVehicles(VehicleManager& Manager)
    {
        Manager.DispatchCollection(Stored);
    }
};
