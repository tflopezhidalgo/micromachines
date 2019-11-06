# EntityStatus ![Build EntityStatus](https://travis-ci.com/tomasLopezHidalgo/micromachines.svg?token=oxmxJLZdAcWRA9wdCzqo&branch=master)

# Reglas para el repo

- Mantener siempre un branch *master* con una versión estable (y aprobada por todos)
- Mantener un branch *development* en el cuál se ve el histórico de los desarrollos
- **Hacer pull antes que push** 
- Resolver los conflictos de merge localmente

# Reglas para código

- Código lindo por favor
- *Keep it simple*
- Programar lo más genéricamente posible
- Testear

# Compile with CMake

```
cd <PATH_TO_MICROMACHINES>/micromachines
mkdir build
cd buildWorld
cmake ..
make <CLIENT/SERVER>
```
