#include "Seat.h"
#include "../Biological/Person.h"
#include "../../Net/NetControlDevice/NetControlDevice.h"
#include <nlohmann/json.hpp>

Seat::Seat(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) :
    Entity(name, "Seat", parent, nodePos, hp)
{
    this->m_isDrawUi = false;
    this->m_netControl = new NetControlDevice(name + std::to_string(this->GetId()));

    sf::Texture * seat = ResourceManager::GetTexture("seat");
    seat->setSmooth(true);

    auto device = static_cast<NetControlDevice *>(this->m_netControl);

    device->connectAnotherAfterCallBack = [this, device](Net * net2) -> void {
	DeviceSignal signal;
	signal.sender = this;

	DeviceSignalDataJson data;
	nlohmann::json jsonData;
	jsonData["command"] = "seatInfo";
	data.data = jsonData.dump();
	signal.data = &data;

	DeviceSignalDataBool res;
	signal.res = &res;

	device->sendSignal(signal);

    };

    m_mainShape = CreateRectangleShape(b2Vec2(1, 3), seat);
    Graphic::insertKeyCallBack(
	sf::Keyboard::Key::T, GetId(),
	[this]() -> void {
	    if (this->isHavePerson()) {
		m_person->SetPosition(m_pos + GetPosition());
		m_person->m_physicalBody->GetFixture()->m_fixture->SetSensor(false);
		m_person->SetDraw(true);
		m_person = nullptr;
		m_pos = b2Vec2(0, 0);
	    }
	});

    float force = 90;
    Graphic::insertKeyCallBack(
	sf::Keyboard::Key::W, GetId(),
	[force, this]() -> void {
	    if (this->isHavePerson()) {
		this->move(0, force);
	    }
	});
    Graphic::insertKeyCallBack(
	sf::Keyboard::Key::S, GetId(),
	[force, this]() -> void {
	    if (this->isHavePerson()) {
		this->move(1, force);
	    }
	});
    Graphic::insertKeyCallBack(
	sf::Keyboard::Key::A, GetId(),
	[force, this]() -> void {
	    if (this->isHavePerson()) {
		this->move(2, force);
	    }
	});
    Graphic::insertKeyCallBack(
	sf::Keyboard::Key::D, GetId(),
	[force, this]() -> void {
	    if (this->isHavePerson()) {
		this->move(3, force);
	    }
	});
}

Seat::~Seat()
{
}

void Seat::onFace(Person *person)
{
    person->m_physicalBody->GetFixture()->m_fixture->SetSensor(true);
    m_pos = person->GetPosition() - GetPosition();
    person->SetPosition(GetPosition());
    m_person = person;
    m_person->SetDraw(false);
}

void Seat::UpdateSelf(sf::Time &dt)
{
    if (m_person != nullptr) {
        m_person->SetPosition(GetPosition());
    }
}

void Seat::DrawSelf()
{
    if (m_person != nullptr) {
    }
}

bool Seat::isHavePerson()
{
    return this->m_person != nullptr;
}

void Seat::move(int direction, float force)
{
    auto device = static_cast<NetControlDevice *>(this->m_netControl);
    DeviceSignal signal;
    DeviceSignalDataJson data;
    nlohmann::json jsonData;
    jsonData["command"] = "move";
    jsonData["data"] = {
	{
	    "direction", direction
	},
	{
	    "force", force
	}
    };
    data.data = jsonData.dump();
    signal.data = &data;
    DeviceSignalDataBool res;
    signal.res = &res;
    device->sendSignal(signal);
    if (res.data) {
	Log::printLog("Seat move finish\n");
    }
}
