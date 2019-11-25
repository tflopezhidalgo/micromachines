print("Loading Lua Player...")

-- start variables macro
next_position = {
    [-1] = "L", -- IZQUIERDA
    [0] = "F", -- ADELANTE
    [1] = "R", -- DERECHA
    [2] = "B" -- REVERSE
}
-- end variables macro

-- Depende el angulo tiene una direccion a seguir
function getEvent(angle, pos_x, pos_y, real_pos_x, real_pos_y)
    if (pos_y < 12) then
        pos_y = pos_y + 1
    end
    return action(pos_x, pos_y)
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

-- cada tile va a tener una posicion recomendada a avanzar
function next_recommended_position(floor_type)
    if (floor_id[floor_type]["direction"] ~= nil) then
        return floor_id[floor_type]["direction"]
    end
    return next_position[0]
end

function check_floor(floor_type)
    return floor_id[floor_type]["safe"]
end

-- verifica si hay una entidad en la posicion en la que quiere avanzar
function check_entity(pos_x, pos_y)
    for _, entity in pairs(entities) do
        if (entity[2] == pos_x and entity[3] == pos_y) then
            return entities[entity[1]]["safe"]
        end
    end
    -- no hay ninguna entidad en ese lugar, puede pasar
    return true
end

function action(pos_x, pos_y)
    if (is_in_border_bottom(pos_x, pos_y)) then
        return next_position[2]
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
    local st, en = getLimit(pos_y)
    for i = st, en do
        local pos = map[pos_y][pos_x + i]
        if (check_floor(pos) and check_entity(pos)) then
            return next_position[i]
        end
    end
    return next_position[0]
end
