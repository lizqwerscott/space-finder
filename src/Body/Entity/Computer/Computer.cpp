#include "Computer.h"
#include "../Thruster/Thruster.h"
#include "../Gyro/Gyro.h"
#include "../Biological/Person.h"
#include "../Seat/Seat.h"
#include "../../Net/NetUse/NetUse.h"
#include "../../Net/NetControlDevice/NetControlDevice.h"

#include <nlohmann/json.hpp>

Computer::Computer(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) :
    Entity(name, "Computer", parent, nodePos, hp),
    gyro(nullptr)
{
    this->m_netEnergy = new NetUse(10, 1);
    this->m_netControl = new NetControlDevice(name + std::to_string(this->GetId()));

    auto device = static_cast<NetControlDevice *>(this->m_netControl);

    device->subscribeRecive(
	DeviceSignalType::Json,
	[this](DeviceSignal &signal) -> void {
	    auto data = static_cast<DeviceSignalDataJson *>(signal.data);
	    nlohmann::json jsonData = nlohmann::json::parse(data->data);
	    std::string command = jsonData["command"];
	    if (command == "move") {
		auto res = static_cast<DeviceSignalDataBool *>(signal.res);
		int direction = jsonData["data"]["direction"];
		int force = jsonData["data"]["force"];
		this->move(direction, force);
		Log::printLog("Move: direction: %d, force: %d\n", direction, force);
		res->data = true;
	    } else if (command == "thrusterInfo") {
		auto res = static_cast<DeviceSignalDataBool *>(signal.res);
		res->data = true;
		this->addControl(signal.sender);
	    } else if (command == "gyroInfo") {
		auto res = static_cast<DeviceSignalDataBool *>(signal.res);
		res->data = true;
		if (signal.sender->m_typeName == "Gyro" && this->gyro == nullptr) {
		    auto _gyro = static_cast<Gyro *>(signal.sender);
		    this->gyro = _gyro;
		}
	    } else if (command == "seatInfo") {
		auto res = static_cast<DeviceSignalDataBool *>(signal.res);
		res->data = true;
		if (signal.sender->m_typeName == "Seat" && this->m_seat == nullptr) {
		    auto seat = static_cast<Seat *>(signal.sender);
		    this->m_seat = seat;
		}
	    } else {
		std::string command = jsonData["command"];
		Log::printLog("Computer not find this command: %s\n", command.c_str());
	    }
	});

    m_isControl = true;
    m_isConnect = true;
    m_isDrawUi = false;

    sf::Texture * computer = ResourceManager::GetTexture("computer");
    computer->setSmooth(true);

    m_mainShape = CreateRectangleShape(b2Vec2(1, 1), computer);

    Graphic::insertKeyCallBack(sf::Keyboard::Key::U, GetId(), [device, this]() -> void {
	    DeviceSignal signal;
	    signal.sender = this;
	    DeviceSignalDataString dataString;
	    dataString.data = "Hello";
	    signal.data = &dataString;
	    DeviceSignalDataString dataRecive;
	    signal.res = &dataRecive;

	    device->sendSignal(signal);

	    Log::printLog("Computer: Send Recive %s\n", dataRecive.data.c_str());
	});
}

Computer::~Computer()
{
}

void Computer::onFace(Person *person)
{
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[Computer]report computer\n");
    this->m_isDrawUi = !this->m_isDrawUi;
}

void Computer::addControl(Entity * entity)
{
    auto iter = find_if(m_thrusters.begin(), m_thrusters.end(), [entity](Thruster * thruster) -> bool {
        return thruster->GetId() == entity->GetId();
    });
    if (iter == m_thrusters.end()) {
        if (entity->m_typeName == std::string("Thruster")) {
            Thruster * thruster = static_cast<Thruster *>(entity);
            Log::setLevel(LOG_LEVEL_INFO);
            Log::printLog("add thruster\n");
            m_thrusters.push_back(thruster);
        }
    } else {
        if (entity->m_typeName == std::string("Seat")) {
            if (m_seat == nullptr) {
                m_seat = static_cast<Seat *>(entity);
            }
        }
        Log::setLevel(LOG_LEVEL_ERROR);
        Log::printLog("Added, %u\n", entity->GetId());
    }
}

void Computer::DrawUiSelf()
{
    if (m_isDrawUi) {
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
        ImGui::Begin("Computer");

        float force = 100;
        if (ImGui::Button("Up")) {
            move(0, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Down")) {
            move(1, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Left")) {
            move(2, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Right")) {
            move(3, force);
        }
        ImGui::SameLine();
        if (ImGui::Button("Push")) {
            for (auto thruster : m_thrusters) {
                thruster->increaseThrust(10);
                thruster->push();
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("Push\n");
            }
        }
        if (ImGui::Button("GetInfo")) {
            Log::setLevel(LOG_LEVEL_INFO);
            Log::printLog("this angle:%u, %f\n", GetId(), GetAngle());
            for (auto thruster : m_thrusters) {
                Log::printLog("thruster:%u, %f, Direction:%f, %f\n", thruster->GetId(), thruster->GetAngle(), thruster->m_pushDirection.x, thruster->m_pushDirection.y);
            }
        }
        if (ImGui::Button("LoadScripts")) {
            // Script::lisp("(load \"/home/lizqwer/project/Slt-GameEngine/Test/tankTest/Scripts/test.lisp\")");
        }
        ImGui::End();
    }
}

void Computer::move(int direction, float force)
{
    auto wucha = [](float angle1, float angle2, float wuc = 0.1) -> bool {
        return abs(angle1 - angle2) <= 0.1;
    };
    std::vector<Thruster *> _direction;

    switch (direction) {
    case 0: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle())) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    case 1: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle() + PI)) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    case 2: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle() + PI + PI / 2)) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    case 3: {
        for (auto thruster : m_thrusters) {
            float angle = thruster->GetAngle();
            if (wucha(angle, GetAngle() + PI / 2)) {
                _direction.push_back(thruster);
            }
        }
        for (auto thruster : _direction) {
            thruster->setThrust(force);
            thruster->push();
        }
    }
    break;
    default:
        break;
    }
}

void Computer::UpdateSelf(sf::Time &dt)
{
    this->m_netEnergy->UpdateSelf(dt);
    this->m_netControl->UpdateSelf(dt);
    if (this->gyro != nullptr) {
	if (m_seat != nullptr) {
	    this->gyro->start = m_seat->isHavePerson();
	}
    }
}

Computer * Computer::findSelf(int id)
{
    auto entity = static_cast<Entity *>(SceneManager::GetRunScene()->GetRootNode()->GetChild(id));
    if (entity != nullptr && entity->m_typeName == std::string("Computer")) {
        return static_cast<Computer *>(entity);
    } else {
        return nullptr;
    }
}

void Computer::push(int computerId, int id, int force)
{
    Computer * computer = Computer::findSelf(computerId);
    if (computer != nullptr) {
        auto thrusters = computer->m_thrusters;
        auto iter = find_if(thrusters.begin(), thrusters.end(), [id](Thruster * item) -> bool {
            return item->GetId() == (unsigned int)id;
        });

        if (iter != thrusters.end()) {
            Thruster * thruster = *iter;
            thruster->setThrust(force);
            thruster->push();
        }
    }
}

void Computer::sendSignalString(int computerId, std::string data)
{
    Computer * computer = Computer::findSelf(computerId);
    if (computer != nullptr) {
	auto device = static_cast<NetControlDevice *>(computer->m_netControl);
	DeviceSignal signal;
	signal.sender = computer;
	DeviceSignalDataString dataString;
	dataString.data = data;
	signal.data = &dataString;
	DeviceSignalDataString dataRecive;
	signal.res = &dataRecive;

	device->sendSignal(signal);
    }
}

//void Computer::move(int direction, float force)
//{
//}

void Computer::rotate(float angle)
{
}
