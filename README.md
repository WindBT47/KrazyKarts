# KrazyKarts

## Table of Contents

- [Background](#background)
- [Install](#install)
- [Usage](#usage)

## Background

Head First Design Patterns exhorts us **not to reinvent the wheels** unless we plan on learning about the wheels.

So this project is about the **wheels** and it does. Base on the **APawn**, create custom **UActorComponents** for movement and replicate. There is some knowledge about physics and math that you have learned in the university.

## Install

Create one **APawn** class, and create two **UActorComponent** classes for your APawn that you create before. And then copy the code in **GoCart.cpp&h** to the APawn class you create in the last step. Copy the code in **GoCartMovementComponent.cpp&h** and **GoCartMovementReplicator.cpp&h** to the UActorComponent classes respectively.

## Usage

Here are some introductions about each file.

### GoCart.cpp&h

This is an entity APawn of the vehicle. It has two pointers, one **UGoCartMovementComponent\*** and one **UGoCartMovementReplicator\***.

### GoCartMovementComponent.cpp&h

This component is inherited from UActorComponent, and it controls the movement of the vehicle. It has a USTRUCT named FGoCartMove to generalize the state of the vehicle. This class is base on classical physics. The force of the vehicle is the sum of the air resistance, rolling resistance, and the push force from the controller. And then calculate the rotation and the offset by mathematics with the velocity.

### GoCartMovementReplicator.cpp&h

This component is inherited from UActorComponent, and it controls the synchronization of the server and the client. This one is implemented by interpolation like Hermite cubic spline.
