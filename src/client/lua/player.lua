print("Loading Lua Player...")

-- start variables macro
MIN_ANGLE_UP = 45
MAX_ANGLE_UP = 135

MIN_ANGLE_LEFT = 135
MAX_ANGLE_LEFT = 225

MIN_ANGLE_DOWN = 225
MAX_ANGLE_DOWN = 315

MIN_ANGLE_RIGHT1 = 0
MAX_ANGLE_RIGHT1 = 45
MIN_ANGLE_RIGHT2 = 315
MAX_ANGLE_RIGHT2 = 360

next_position = {
    [-1] = "L", -- IZQUIERDA
    [0] = "F", -- ADELANTE
    [1] = "R", -- DERECHA
    ["reverse"] = "B",
    [2] = "B"
}
-- end variables macro

-- Depende el angulo tiene una direccion a seguir
function getEvent(angle, pos_x, pos_y)
    angle = tonumber(string.format("%d", angle))
    print(pos_x)
    print(pos_y)
    local action = ""
    if (angle >= MIN_ANGLE_UP and angle <= MAX_ANGLE_UP) then
        return action_vertical("U", pos_x, pos_y) -- pos_y -1
    end
    if (angle >= MIN_ANGLE_LEFT and angle <= MAX_ANGLE_LEFT) then
        return action_horizontal("L", pos_x, pos_y) -- pos_x -1
    end
    if (angle >= MIN_ANGLE_DOWN and angle <= MAX_ANGLE_LEFT) then
        return action_vertical("D", pos_x, pos_y) --pos_y +1
    end
    if ((angle >= MIN_ANGLE_RIGHT1 and angle <= MAX_ANGLE_RIGHT1) or
        (angle >= MIN_ANGLE_RIGHT2 and angle <= MAX_ANGLE_RIGHT2)) then
        return action_horizontal("R", pos_x, pos_y) --pos_x +1
    end
    return action
end

-- Si esta en un borde no tiene pasar el limite
function getLimit(pos)
    local start = -1
    local ending = 1
    if (pos == 1) then
        start = 0
    end
    if (pos == #map) then
        ending = 0
    end
    return start, ending
end

function is_in_border(pos)
    return pos <= 1 or pos >= #map
end

function next_recommended_position(floor_type, direction)
    print(floor_id[floor_type]["name"])
    return floor_id[floor_type]["direction"]
end

function check_floor(floor_type)
    return floor_id[floor_type]["safe"]
end

function check_entity(pos_x, pos_y)
    for _, entity in pairs(entities) do
        if (entity[2] == pos_x and entity[3] == pos_y) then
            return entities[entity[1]]["safe"]
        end
    end
    -- no hay ninguna entidad en ese lugar, puede pasar
    return true
end

function action_vertical(direction, pos_x, next_y)
    if (is_in_border(next_y)) then
        return next_position["reverse"]
    end

    -- cada piso tiene una direccion recomendada a avanzar
    -- checkeo que la posicion es segura en las entidades y si es segura avanzo
    -- si no pruebo con otra direccion: -1 0 1 y eso lo relaciona R F L
    local try_pos = next_recommended_position(map[next_y][pos_x], direction)
    if (check_entity(map[next_y][pos_x + try_pos])) then
        return next_position[try_pos]
    end
    local st, en = getLimit(pos_x)
    for i = st, en do
        local pos = map[next_y][pos_x + i]
        if (check_floor(pos) and check_entity(pos)) then
            return next_position[i]
        end
    end
    return next_position[0]
end

function action_horizontal(direction, next_x, pos_y)
    if (is_in_border(next_x)) then
        return next_position["reverse"]
    end

    local try_pos = next_recommended_position(map[pos_y][next_x], direction)
    if (next_y_try ~= nil and check_entity(map[pos_y][next_x + try_pos])) then
        return next_position[try_pos]
    end
    local st, en = getLimit(pos_x)
    for i = st, en do
        local pos = map[pos_y][next_x + i]
        if (check_floor(pos) and check_entity(pos)) then
            return next_position[i]
        end
    end
    print("fin")
    print(try_pos)
    print(next_position[try_pos])
    return next_position[0]
end
