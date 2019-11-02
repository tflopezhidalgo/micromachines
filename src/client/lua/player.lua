print("Loading Lua Player...\n")

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

function getAction(angle, pos_x, pos_y)
    local action = ""
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

function getStart(pos_x)
    start = -1
    if (pos_x == map_start) then
        start = 0
    end
    return start
end

function getEnd(pos_x)
    ending = 1
    if (pos_x == map_end) then
        ending = 0
    end
    return ending
end

function is_in_border(pos)
    return pos == map_start or pos == map_end
end

function check_position(position)
    return entities[position]["safe"]
end

function direction_down(pos_x, pos_y)
    -- y + 1
    -- x (-1, 0, 1)
    if (is_in_border(pos_y)) then
        return next_position["reverse"]
    end
    local st = getStart(pos_x)
    local en = getEnd(pos_x)
    for i = st, en do
        if (check_position(map[pos_x + i][pos_y + 1])) then
            print(string.format("next: %s", next_position[i]))
            return next_position[i]
        end
    end
end

function direction_up(pos_x, pos_y)
    -- y -1
    -- x (-1, 0, 1)
    if (is_in_border(pos_y)) then
        return next_position["reverse"]
    end
    local st = getStart(pos_x)
    local en = getEnd(pos_x)
    for i = st, en do
        if (check_position(map[pos_x + i][pos_y - 1])) then
            print(string.format("next: %s", next_position[i]))
            return next_position[i]
        end
    end
end

function direction_left(pos_x, pos_y)
    -- x -1
    -- y (-1, 0, 1)
    if (is_in_border(pos_x)) then
        return next_position["reverse"]
    end
    local st = getStart(pos_x)
    local en = getEnd(pos_x)
    for i = st, en do
        if (check_position(map[pos_x - 1][pos_y + i])) then
            print(string.format("next: %s", next_position[i]))
            return next_position[i]
        end
    end
end

function direction_right(pos_x, pos_y)
    -- x + 1
    -- y (-1, 0, 1)
    if (is_in_border(pos_x)) then
        return next_position["reverse"]
    end
    local st = getStart(pos_x)
    local en = getEnd(pos_x)
    for i = st, en do
        if (check_position(map[pos_x + 1][pos_y + i])) then
            print(string.format("next: %s", next_position[i]))
            return next_position[i]
        end
    end
end

function try_go_forward(next_x, next_y)

end

