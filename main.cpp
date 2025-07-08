#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

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

    const LevelInfos& GetBids() const { return this->bids_; }
    const LevelInfos& GetAsks() const { return this->asks_; }

private:
    LevelInfos bids_;
    LevelInfos asks_;
};

class Order {
public:
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
        : orderType_{orderType}
        , orderId_{orderId}
        , side_{side}
        , price_{price}
        , initialQuantity_{quantity}
        , remainingQuantity_{quantity}
    {}

    OrderId GetOrderId() const { return this->orderId_; }
    Side GetSide() const { return this->side_; }
    OrderType GetOrderType() const { return this->orderType_; }
    Quantity GetInitalQuantity() const { return this->initialQuantity_; }
    Quantity GetRemainingQuantity() const { return this->remainingQuantity_; }
    Quantity GetFilledQuantity() const { return this->initialQuantity_ - this->remainingQuantity_; }

    void Fill(Quantity quantity)
    {
        if (quantity > this->GetRemainingQuantity())
            throw std::logic_error("Order (" + std::to_string(this->GetOrderId()) + ") cannot be filled for more than its remaining quantity");
        this->remainingQuantity_ -= quantity;
    }

private:
    OrderType orderType_;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;
};

int main()
{
    Order myOrder(OrderType::GoodTillCancel, 1001, Side::Buy, 1500, 10);

    std::cout << "Order ID: " << myOrder.GetOrderId() << "\n";
    std::cout << "Side: " << (myOrder.GetSide() == Side::Buy ? "Buy" : "Sell") << "\n";
    std::cout << "Type: " << (myOrder.GetOrderType() == OrderType::GoodTillCancel ? "GTC" : "FAK") << "\n";
    std::cout << "Initial Quantity: " << myOrder.GetInitalQuantity() << "\n";
    std::cout << "Remaining Quantity: " << myOrder.GetRemainingQuantity() << "\n";
    std::cout << "Filled Quantity: " << myOrder.GetFilledQuantity() << "\n";

    std::cout << "\nFilling 4 units...\n";
    myOrder.Fill(4);

    std::cout << "Remaining Quantity after fill: " << myOrder.GetRemainingQuantity() << "\n";
    std::cout << "Filled Quantity after fill: " << myOrder.GetFilledQuantity() << "\n";

    try {
        myOrder.Fill(7);
    } catch (const std::logic_error& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
