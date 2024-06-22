#include "Gyro.h"
#include "../../Net/NetControlDevice/NetControlDevice.h"
#include <nlohmann/json.hpp>

Gyro::Gyro(std::string name, GameObject * parent, b2Vec2 size, b2Vec2 nodePos, double hp) :
    Entity(name, "Gyro", parent, nodePos, hp),
    start(false)
{
    this->m_netControl = new NetControlDevice(name + std::to_string(this->GetId()));

    auto device = static_cast<NetControlDevice *>(this->m_netControl);

    device->connectAnotherAfterCallBack = [this, device](Net * net2) -> void {
	DeviceSignal signal;
	signal.sender = this;

	DeviceSignalDataJson data;
	nlohmann::json jsonData;
	jsonData["command"] = "gyroInfo";
	data.data = jsonData.dump();
	signal.data = &data;

	DeviceSignalDataBool res;
	signal.res = &res;

	device->sendSignal(signal);
    };

    this->m_isDrawUi = false;

    sf::Texture * gyro = ResourceManager::GetTexture("gyro");
    gyro->setSmooth(true);

    m_mainShape = CreateRectangleShape(size, gyro);

    // Graphic::insertKeyCallBack(
    // 	sf::Keyboard::Key::Q,
    // 	GetId(),
    // 	[this]() -> void {
    // 	    // this->GetPhysicalBody()->GetBody()->ApplyTorque(10, true);
    // 	    rotate(-10);
    // 	});
    // Graphic::insertKeyCallBack(
    // 	sf::Keyboard::Key::E,
    // 	GetId(),
    // 	[this]() -> void {
    // 	    // this->GetPhysicalBody()->GetBody()->ApplyTorque(-10, true);
    // 	    rotate(10);
    // 	});
}

Gyro::~Gyro()
{

}

void Gyro::UpdateSelf(sf::Time & dt)
{
    if (false) {
	b2Vec2 mousePos = Graphic::getMousePositionP();

	b2Vec2 mainPos = this->GetPosition();
	b2Vec2 nowFace = Math::UnitVector(mousePos - GetPosition());
	float targetAngle = atan2f(-nowFace.x, nowFace.y);
	rotate(targetAngle);
    }
}

void Gyro::rotate(float angle)
{
    //rotate physical body
    float degreeRad = PI / 180;

    b2Body * body = m_physicalBody->GetBody();

    float bodyAngle = body->GetAngle();
    float nextAngle = bodyAngle + body->GetAngularVelocity() / 60.0;
    float totalRotation = angle - nextAngle;
    while ( totalRotation < -180 * degreeRad ) totalRotation += 360 * degreeRad;
    while ( totalRotation >  180 * degreeRad ) totalRotation -= 360 * degreeRad;
    float desiredAngularVelocity = totalRotation * 60;
    float torque = body->GetInertia() * desiredAngularVelocity / (1/60.0);
    body->ApplyTorque(torque, true);
}
