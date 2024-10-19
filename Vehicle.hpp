#pragma once

#include <vector>
#include <unordered_map>

#include "Product.hpp"

class Vehicle
{

private:

    int WeightCapacity = 0;
    int CurrentWeightCapacity = 0;
    std::vector<Product> Stored;
    char VehicleName = '?';

    std::vector<size_t> AverageCount;
    std::vector<int> AverageWeight;
    std::unordered_map<char, int> AverageName;
    std::unordered_map<WrapperType, int> AverageWrapper;

public:

    Vehicle() = delete;
    Vehicle& operator=(const Vehicle&) = delete;
    Vehicle(const Vehicle&) = delete;

    Vehicle(int NewCapacity, char NewName)
        : WeightCapacity(NewCapacity), VehicleName(NewName)
    {

    }

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle)
    {
        os << "Name: " << vehicle.VehicleName << " Capacity: " << vehicle.WeightCapacity;
        return os;
    }

    bool Fill(Product Product)
    {
        if (CurrentWeightCapacity + Product.Weight > WeightCapacity)
        {
            return false;
        }
        Stored.push_back(Product);
        CurrentWeightCapacity += Product.Weight;
        return true;
    }

    const int GetWeightCapacity() const
    {
        return WeightCapacity;
    }

    const int GetCurrentWeightCapacity() const
    {
        return CurrentWeightCapacity;
    }

    void DispatchDelivery()
    {
        if (Stored.size() == 0)
        {
            return;
        }

        AverageCount.push_back(Stored.size());
        AverageWeight.push_back(CurrentWeightCapacity);

        for (const auto& Product : Stored)
        {
            AverageName[Product.Name]++;
            AverageWrapper[Product.Wrapper]++;
        }

        Stored.clear();
        CurrentWeightCapacity = 0;
    }

    void PrintAverages() const
    {
        if (AverageCount.size() == 0)
        {
            std::cout << "\nVehicle " << VehicleName << " was never used to deliver, so no stats \n";
            return;
        }

        std::cout << "\nStats for vehicle " << VehicleName << ": \n";
        
        size_t TempAverage = 0;
        for (const auto& Count : AverageCount)
        {
            TempAverage += Count;
        }
        
        std::cout << "Products on average: " << TempAverage / AverageCount.size() << "\n";
        
        int TempWeight = 0;
        for (const auto& Count : AverageWeight)
        {
            TempWeight += Count;
        }

        std::cout << "Weight on average: " << TempWeight / AverageWeight.size() << "\n";

        char NameKey = '?';
        int NameTemp = 0;
        for (const auto& Count : AverageName)
        {
            if (Count.second > NameTemp)
            {
                NameKey = Count.first;
                NameTemp = Count.second;
            }
        }

        std::cout << "Product on average: " << NameKey << "\n";

        WrapperType WrapperKey = WrapperType::Cardboard;
        int WrapperTemp = 0;
        for (const auto& Count : AverageWrapper)
        {
            if (Count.second > WrapperTemp)
            {
                WrapperKey = Count.first;
                WrapperTemp = Count.second;
            }
        }

        std::cout << "Wrapper on average: " << WrapperKey << "\n";
    }

};
