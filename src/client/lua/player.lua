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
    print("lua:" ,pos_x, pos_y)

    local action = ""
    angle = 0
    if ((angle >= MIN_ANGLE_UP and angle <= MAX_ANGLE_UP) or
            (angle >= MIN_ANGLE_DOWN and angle <= MAX_ANGLE_LEFT)) then
        return action_vertical(pos_x, pos_y) -- pos_y -1 /+1
    end
    if ((angle >= MIN_ANGLE_LEFT and angle <= MAX_ANGLE_LEFT) or
            ((angle >= MIN_ANGLE_RIGHT1 and angle <= MAX_ANGLE_RIGHT1) or
                    (angle >= MIN_ANGLE_RIGHT2 and angle <= MAX_ANGLE_RIGHT2))) then
        return action_horizontal(pos_x, pos_y) -- pos_x -1 / +1
    end
    return next_position[0]
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

function is_in_border_bottom(pos_x, pos_y)
    local border_x = false
    if (pos_x > #map[1]) then
        border_x = true
    end
    local border_y = false
    if (pos_y > #map) then
        border_y = true
    end
    return border_x or border_y
end

function is_in_border_top(pos_x, pos_y)
    local border_x = false
    if (pos_x <= 1) then
        border_x = true
    end
    local border_y = false
    if (pos_y <= 1) then
        border_y = true
    end
    return border_x or border_y
end

function next_recommended_position(floor_type)
    print(floor_id[floor_type]["name"], floor_type)
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

function action_vertical(pos_x, pos_y)
    if (is_in_border_bottom(pos_x, pos_y)) then
        return next_position[0]
    end
    if (is_in_border_top(pos_x, pos_y)) then
        return next_position[2]
    end

    -- cada piso tiene una direccion recomendada a avanzar
    -- checkeo que la posicion es segura en las entidades y si es segura avanzo
    -- si no pruebo con otra direccion: -1 0 1 y eso lo relaciona R F L
    local try_pos = next_recommended_position(map[pos_y][pos_x])
    if (check_entity(map[pos_y][pos_x + try_pos])) then
        return next_position[try_pos]
    end
    local st, en = getLimit(pos_x)
    for i = st, en do
        local pos = map[pos_y][pos_x + i]
        if (try_pos ~= nill and check_floor(pos) and check_entity(pos)) then
            return next_position[i]
        end
    end
    return next_position[0]
end

function action_horizontal(pos_x, pos_y)
    if (is_in_border_bottom(pos_x, pos_y)) then
        return next_position[0]
    end
    if (is_in_border_top(pos_x, pos_y)) then
        return next_position[1]
    end

    local try_pos = next_recommended_position(map[pos_y][pos_x])
    if (check_entity(map[pos_y][pos_x + try_pos])) then
        return next_position[try_pos]
    end
    local st, en = getLimit(pos_y)
    for i = st, en do
        local pos = map[pos_y][pos_x + i]
        if (check_floor(pos) and check_entity(pos)) then
            return next_position[i]
        end
    end
    return next_position[0]
end
