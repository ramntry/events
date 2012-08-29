TEMPLATE = app
CONFIG += console
CONFIG -= qt

INCLUDEPATH += core \
    cars

SOURCES += main.cpp \
    core/Object.cpp \
    cars/Car.cpp \
    cars/parts/Wheel.cpp \
    cars/parts/Engine.cpp \
    cars/Mazda.cpp \
    core/Event.cpp \
    core/MetaObject.cpp \
    cars/Truck.cpp \
    core/EventQueue.cpp

HEADERS += \
    core/Object.hpp \
    cars/Car.hpp \
    cars/parts/Wheel.hpp \
    cars/parts/Engine.hpp \
    cars/Mazda.hpp \
    core/Event.hpp \
    core/MetaObject.hpp \
    cars/Truck.hpp \
    core/EventQueue.hpp

