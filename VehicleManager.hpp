#pragma once

#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "Util.hpp"
#include "Vehicle.hpp"

class VehicleManager
{
private:

    std::vector<std::unique_ptr<Vehicle>> Vehicles;

public:

    VehicleManager() = delete;

    VehicleManager(int MaxFactoryWeightProduction)
    {
        std::mt19937_64 gen;
        auto seed = std::random_device{}();
        gen.seed(seed);
        std::uniform_int_distribution<int> weight_distribution(9000, 16000);

        int VehicleCounter = 0;

        while (true)
        {
            char VehicleName = IndexToCapitalLetter(VehicleCounter);
            int Capacity = weight_distribution(gen);

            std::unique_ptr<Vehicle> NewVehicle = std::make_unique<Vehicle>(Capacity, VehicleName);
            std::cout << "Creating vehicle #[" << VehicleCounter + 1 << "]: " << *NewVehicle.get() << std::endl;
            Vehicles.push_back(std::move(NewVehicle));

            VehicleCounter++;

            MaxFactoryWeightProduction -= Capacity;

            if (MaxFactoryWeightProduction < 0)
            {
                break;
            }
        }
    }

    void DispatchCollection(std::vector<Product>& Products)
    {
        std::mutex Mutex;

        std::vector<std::thread> Threads;

        for (auto& Vehicle : Vehicles)
        {
            while (true)
            {
                if (Products.size() == 0)
                {
                    break;
                }

                Product& TargetProduct = Products.at(Products.size() - 1);

                if (!Vehicle->Fill(TargetProduct))
                {
                    break;
                }
                else
                {
                    Products.pop_back();
                }
            }

            std::thread t([&Vehicle, &Mutex]()
                {
                    if (Mutex.try_lock())
                    {
                        Vehicle->DispatchDelivery();
                        Mutex.unlock();
                    }
                });
            Threads.push_back(std::move(t));
        }

        for (auto& Thread : Threads)
        {
            Thread.join();
        }
    }

    void PrintAverages()
    {
        for (const auto& Vehicle : Vehicles)
        {
            Vehicle->PrintAverages();
        }
    }
};
