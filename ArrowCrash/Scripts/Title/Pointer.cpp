#include "Pointer.h"


const int Pointer::radius = 15;
const double Pointer::accel = 2.0;
const double Pointer::frictionCoeff = 1.0;
const double Pointer::maxSpeed = 10.0;

Pointer::Pointer(int player_num_)
	:pos(Window::Center()),
	velocity(0, 0),
	player_num(player_num_),
	color(constants::playerColor[player_num])
{}


void Pointer::move() {
	//���̓x�N�g���𐳋K��
	Vec2 input = Vec2((Input::KeyRight.pressed - Input::KeyLeft.pressed), (Input::KeyDown.pressed - Input::KeyUp.pressed));
	if (!input.isZero()) input.normalize();
	
	//�����E����
	velocity += input * accel - (velocity.isZero() ? Vec2::Zero : velocity.normalized()) * frictionCoeff;
	
	//���x�̏���E����
	double speed = velocity.length();
	if (speed < frictionCoeff) velocity.set(0, 0);
	else if (speed > maxSpeed) {
		velocity -= (speed - maxSpeed) * velocity.normalized();
	}

	pos.moveBy(velocity);
}

bool Pointer::isOutOfRegion() const {
	return !Window::ClientRect().contains(pos);
}

bool Pointer::isClicked() const {
	return Input::KeySpace.clicked;
}

Point Pointer::getPos() const {
	return pos.asPoint();
}

void Pointer::update() {
	move();
	while (isOutOfRegion()) {
		pos.moveBy(-velocity.normalized());
	}
}


void Pointer::draw() const {
	PutText(velocity).from(0, 0);
	Circle(pos, radius).drawFrame(2.0, 0.5, color);
	Circle(pos, radius / 5).draw(color);
}