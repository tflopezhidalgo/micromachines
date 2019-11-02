print("Loading Lua Player...")

-- start variables macro
map_end = 20
map_start = 1

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

next_position = {
    [-1] = "R",
    [0] = "F",
    [1] = "L",
    ["reverse"] = "B"
}
-- end variables macro


-- Depende el angulo tiene una direccion a seguir
function getAction(angle, pos_x, pos_y)
    local action = ""
    print(pos_x, pos_y)
    if (angle >= min_angle_up and angle <= max_angle_up) then
        action = direction_up(pos_x, pos_y)

    elseif (angle >= min_angle_left and angle <= max_angle_left) then
        action = direction_left(pos_x, pos_y)

    elseif (angle >= min_angle_down and angle <= max_angle_down) then
        action = direction_left(pos_x, pos_y)

    elseif ((angle >= min_angle_right1 and angle <= max_angle_right1) or
        (angle >= min_angle_right2 and angle <= max_angle_right2)) then
        action = direction_right(pos_x, pos_y)
    end
    return action
end

-- Si esta en un borde no tiene pasar el limite
function getLimit(pos)
    start = -1
    ending = 1
    if (pos == map_start) then
        start = 0
    end
    if (pos == map_end) then
        ending = 0
    end
    return start, ending
end

function is_in_border(pos)
    return pos == map_start or pos == map_end
end

function check_position(position)
    return entities[position]["safe"]
end

function direction_down(pos_x, pos_y)
    if (is_in_border(pos_y)) then
        return next_position["reverse"]
    end

     if (check_position(map[pos_y + 1][pos_x])) then
        return next_position[0]
    end

    local st, en = getLimit(pos_x)
    for i = st, en do
        if (check_position(map[pos_y + 1][pos_x + i])) then
            return next_position[i]
        end
    end
    return "F"
end

function direction_up(pos_x, pos_y)
    if (is_in_border(pos_y)) then
        return next_position["reverse"]
    end
    if (check_position(map[pos_y - 1][pos_x])) then
        return next_position[0]
    end

    local st, en = getLimit(pos_x)
    for i = st, en do
        print(map[pos_y - 1][pos_x + i])
        if (check_position(map[pos_y - 1][pos_x + i])) then
            print(string.format("next: %s", next_position[i]))
            return next_position[i]
        end
    end
    return "F"
end

function direction_left(pos_x, pos_y)
    if (is_in_border(pos_x)) then
        return next_position["reverse"]
    end

    if (check_position(map[pos_y][pos_x - 1])) then
        return next_position[0]
    end

    local st, en = getLimit(pos_y)
    for i = st, en do
        if (check_position(map[pos_y + i][pos_x - 1])) then
            return next_position[i]
        end
    end
    return "F"
end

function direction_right(pos_x, pos_y)
    if (is_in_border(pos_x)) then
        return next_position["reverse"]
    end

    if (check_position(map[pos_y][pos_x + 1])) then
        return next_position[0]
    end

    local st, en = getLimit(pos_y)
    for i = st, en do
        if (check_position(map[pos_y + i][pos_x + 1])) then
            return next_position[i]
        end
    end
    return "F"
end
