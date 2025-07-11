#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>


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

using OrderPointer = std::shared_ptr<Order>;

using OrderPointers = std::list<OrderPointer>;

class OrderModify
{
public:
    OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
        : orderId_{ orderId }
        , price_{ price }
        , side_{ side }
        , quantity_{ quantity }
    { }

    OrderId GetOrderId() const { return orderId_; }
    Price GetPrice() const { return price_; }
    Side GetSide() const { return side_; }
    Quantity GetQuantity() const { return quantity_; }

    OrderPointer ToOrderPointer(OrderType type) const
    {
        return std::make_shared<Order>(type, GetOrderId(), GetSide(), GetPrice(), GetQuantity());
    }

private:
    OrderId orderId_;
    Price price_;
    Side side_;
    Quantity quantity_;
};

int main()
{
    return 0;
}
