
#ifndef MICROMACHINES_MACROS_H
#define MICROMACHINES_MACROS_H


//Sv macros
#define BACKLOG 5
#define QUIT_ACTION 'Q'


//Serializing sv-client rescailing
#define SERIALIZING_RESCAILING 1000


//Protocol sv-client messages
#define CREATE_MATCH_MSG "create"
#define VALID 0
#define MATCH_HAS_STARTED 1
#define MATCH_EQUAL_NAMED 2
#define CLIENT_EQUAL_NAMED 3


//Movement ID's
#define FORWARD 'W'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'

//Bodies sizes //todo adjust sizes
#define CAR_H 15.f
#define CAR_W 6.f
#define STONE_RADIUS 3.f
#define OIL_RADIUS 5.f
#define BOOSTERS_RADIUS 3.f
#define EDGE_THICKNESS 0.5f
#define TRACK_SIZE 33

//Config Keys
#define MAX_FORWARD_SPEED_KEY "maxForwardSpeed"
#define MAX_BACKWARD_SPEED_KEY "maxBackwardSpeed"
#define FRONT_MAX_DRIVE_FORCE_KEY "frontTireMaxDriveForce"
#define BACK_MAX_DRIVE_FORCE_KEY "backTireMaxDriveForce"
#define FRONT_MAX_LAT_IMPULSE_KEY "frontTireMaxLateralImpulse"
#define BACK_MAX_LAT_IMPULSE_KEY "backTireMaxLateralImpulse"
#define FPS_KEY "framesPerSecond"
#define HEALTH_BOOST_KEY "healthBoost"
#define OIL_GRIP_KEY "oilGrip"
#define TRACK_FRICTION_KEY "trackFriction"
#define GRASS_FRICTION_KEY "grassFriction"
#define CAR_COLLISION_DAMAGE_KEY "carCollisionDamage"
#define SPEED_BOOST_KEY "speedBoost"
#define STONE_DAMAGE_KEY "stoneDamage"

#endif //MICROMACHINES_MACROS_H
