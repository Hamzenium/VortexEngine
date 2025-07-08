#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <vector> // Needed for std::vector

enum class OrderType {
    GoodTillCancel,
    FillAndKill
};

enum class Side {
    Buy,
    Sell
};

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;

struct LevelInfo {
    Price price_;
    Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>;

class OrderbookLevelInfos {
public:
    OrderbookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
        : bids_{bids}
        , asks_{asks}
    {}

    const LevelInfos& GetBids() const { return bids_; }
    const LevelInfos& GetAsks() const { return asks_; }

private:
    LevelInfos bids_;
    LevelInfos asks_;
};

int main()
{
    // Example usage
    LevelInfos bids = { {100, 10}, {99, 15} };
    LevelInfos asks = { {101, 5}, {102, 20} };

    OrderbookLevelInfos ob(bids, asks);

    std::cout << "Bids:" << std::endl;
    for (const auto& lvl : ob.GetBids()) {
        std::cout << "Price: " << lvl.price_ << ", Qty: " << lvl.quantity_ << std::endl;
    }

    std::cout << "Asks:" << std::endl;
    for (const auto& lvl : ob.GetAsks()) {
        std::cout << "Price: " << lvl.price_ << ", Qty: " << lvl.quantity_ << std::endl;
    }

    return 0;
}
