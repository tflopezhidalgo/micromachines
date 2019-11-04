print("Loading Lua Player...")

-- start variables macro
min_angle_up = 45
max_angle_up = 135

min_angle_left = 135
max_angle_left = 225

min_angle_down = 225
max_angle_down = 315

min_angle_right1 = 0
max_angle_right1 = 45
min_angle_right2 = 315
max_angle_right2 = 360

-- end variables macro


-- Depende el angulo tiene una direccion a seguir
function getAction(angle, pos_x, pos_y)
    local action = ""
    if (angle >= min_angle_up and angle <= max_angle_up) then
        action = action_vertical("U", pos_x, pos_y - 1)

    elseif (angle >= min_angle_left and angle <= max_angle_left) then
        action = action_horizontal("L", pos_x - 1, pos_y)

    elseif (angle >= min_angle_down and angle <= max_angle_down) then
        action = action_vertical("D", pos_x, pos_y +1)

    elseif ((angle >= min_angle_right1 and angle <= max_angle_right1) or
        (angle >= min_angle_right2 and angle <= max_angle_right2)) then
        action = action_horizontal("R", pos_x + 1, pos_y)
    end
    return action
end

-- Si esta en un borde no tiene pasar el limite
function getLimit(pos)
    start = -1
    ending = 1
    if (pos == 1) then
        start = 0
    end
    if (pos == #map) then
        ending = 0
    end
    return start, ending
end

function is_in_border(pos)
    return pos == 1 or pos == #map
end

function check_position(position)
    return floor_id[position]["safe"]
end

function check_safe_floor(direction, floor)
    if (floor_id[floor]["direction"] ~= nil) then
        return floor_id[floor]["direction"]
    else
        return "F" -- ADELANTE
    end
end

function action_vertical(direction, pos_x, next_y)
    if (is_in_border(pos_y)) then
        return "B" -- REVERSE
    end

    -- return check_safe_floor(direction, map[next_y][pos_x + i])
    local st, en = getLimit(pos_x)
    for i = st, en do
        local floor = map[next_y][pos_x + i])
        if (check_position(floor)) then
            return "F"
        end
    end
end

function action_horizontal(direction, next_x, pos_y)
    if (is_in_border(pos_x)) then
        return "B" -- REVERSE
    end

    local st, en = getLimit(pos_y)
    for i = st, en do
        if (check_position(map[pos_y + i][next_x])) then
            return "F"
        end
    end
    return "F"
end

function check_entity(pos_x, pos_y)
    for _, entity in pairs(entities) do
        if (entity[2] == pos_x and entity[3] == pos_y) then
            return entities[entity[1]]["safe"]
    end
    -- no hay ninguna entidad en ese lugar, puede pasar
    return true
end
