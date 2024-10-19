#include <vector>

#include "FactoryManager.hpp"
#include "Warehouse.hpp"
#include "VehicleManager.hpp"


int main()
{
    static constexpr unsigned int N = 75; // > 50
    static constexpr unsigned int M = 125; // > 100
    static constexpr unsigned int FactoryCount = 5; // > 3
    static constexpr unsigned int RunSimulationInHours = 500;

    FactoryManager FactoryManager(FactoryCount, N);

    int WarehouseCapacity = M * FactoryManager.GetFactoriesProduction();

    Warehouse Warehouse(WarehouseCapacity);

    VehicleManager VehicleManager(FactoryManager.GetFactoriesMaxWeightProduction());

    for (size_t i = 0; i < RunSimulationInHours; i++)
    {
        std::cout << "\nRunning hour " << i + 1 << "\n";

        std::vector<FactoryManager::FactoryProduction> FactoryProduction;

        // Multithreaded
        FactoryManager.GatherProducts(FactoryProduction);
        
        if (Warehouse.IsCloseToFull())
        {
            // Multithreaded
            Warehouse.DispatchVehicles(VehicleManager);
        }

        for(auto& Production : FactoryProduction)
        {
            std::cout << "Filling storage with " << Production.ProducedProducts.size() << " products from factory " << Production.FactoryName << "\n";
            Warehouse.FillStorage(Production.ProducedProducts);
        }
    }

    VehicleManager.PrintAverages();

}
