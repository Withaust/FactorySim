#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <mutex>

#include "Util.hpp"
#include "Factory.hpp"

class FactoryManager
{
private:

    std::vector<std::unique_ptr<Factory>> Factories;

public:

    struct FactoryProduction
    {
        char FactoryName = '?';
        std::vector<Product> ProducedProducts;
    };

    FactoryManager() = delete;

    FactoryManager(int FactoryCount, const int N)
    {
        std::mt19937_64 gen;
        auto seed = std::random_device{}();
        gen.seed(seed);
        std::uniform_real_distribution<float> float_distribution(-0.3f, 0.3f);
        std::uniform_int_distribution<int> weight_distribution(10, 128);
        std::uniform_int_distribution<int> wrapper_distribution(0, static_cast<int>(WrapperType::Max) - 1);

        for (int i = 0; i < FactoryCount; ++i)
        {
            int ProductsPerHour = static_cast<int>(N + (N * float_distribution(gen)));
            char FactoryName = IndexToCapitalLetter(i);
            char ProductName = IndexToLowercaseLetter(i);
            int ProductWeight = weight_distribution(gen);
            WrapperType ProductWrapper = static_cast<WrapperType>(wrapper_distribution(gen));

            std::unique_ptr<Factory> NewFactory = std::make_unique<Factory>(ProductsPerHour, FactoryName, ProductName, ProductWeight, ProductWrapper);
            std::cout << "Creating factory #[" << i + 1 << "]: " << *NewFactory.get() << "\n";
            Factories.push_back(std::move(NewFactory));
        }

        std::cout << "\n";
    }

    void GatherProducts(std::vector<FactoryProduction>& Production)
    {
        std::mutex Mutex;

        std::vector<std::thread> Threads;

        for (const auto& Factory : Factories)
        {
            std::thread t([&Factory, &Mutex, &Production]()
                {
                    FactoryProduction NewProduction;
                    NewProduction.FactoryName = Factory->GetFactoryName();
                    Factory->Produce(NewProduction.ProducedProducts);
                    if (Mutex.try_lock())
                    {
                        Production.push_back(NewProduction);
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

    int GetFactoriesMaxWeightProduction()
    {
        int Result = 0;

        for (const auto& Factory : Factories)
        {
            Result += Factory->GetProductsPerHour() * Factory->GetProductsWeight();
        }

        return Result;
    }

    int GetFactoriesProduction()
    {
        int Result = 0;

        for (const auto& Factory : Factories)
        {
            Result += Factory->GetProductsPerHour();
        }

        return Result;
    }
};
