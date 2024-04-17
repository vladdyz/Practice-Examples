#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

enum class roastType {
    Light, Medium, Dark
};

struct Coffee {
    std::string name;
    roastType roast;
    std::string flavorProfile;
    double pricePerKG;
};

std::list<Coffee> createSubscription(std::vector<Coffee> stock) {
    //Print the number of coffees that are creamy or full bodied
    auto twoFlavorCoffees = std::count_if(stock.begin(), stock.end(), [](const Coffee& c) {
        return c.flavorProfile == "Creamy" || c.flavorProfile == "Full Bodied";
        });
    std::cout << "There are " << twoFlavorCoffees << " in Stock that are Creamy or Full Bodied" << std::endl;

    // Sort through the coffees based on roastType 
    std::sort(stock.begin(), stock.end(), [](const Coffee& cur, const Coffee& next) {
        return cur.roast < next.roast;
        });

    std::list<Coffee> ret;

    //Make a new container with only the light and medium roasts where price is less than 10/kg
    std::for_each(stock.begin(), stock.end(), [&](const Coffee& cof) {
        if ((cof.roast == roastType::Light || cof.roast == roastType::Medium) && cof.pricePerKG < 10) {
            ret.push_back(cof);
        }
        });

    // Add to the previous container the first dark roast in the original container
    auto darkRoast = std::find_if(stock.begin(), stock.end(), [](const Coffee& cof) {
        return cof.roast == roastType::Dark;
        });
    if (darkRoast != stock.end()) {
        ret.push_back(*darkRoast);
    }

    // Tally up the total price per KG of all the coffees in the new container
    auto cost = std::accumulate(ret.begin(), ret.end(), 0.0, [](double sum, const Coffee& cof) {
        return sum + cof.pricePerKG;
        });
    std::cout << "The total cost of the subscription is: $" << cost << std::endl;

    return ret;
}