print("Loading Lua Player...")

-- start variables macro
map_end = 20
map_start = 1

next_position = {
    [0] = "R",
    [1] = "F",
    [2] = "L",
    ["reverse"] = "B"
}
-- end variables macro

function check_position(position)
    return entities[position]["safe"]
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

function is_top(pos_y)
    return pos_y == map_start
end

function getAction(pos_x, pos_y)
    -- print(string.format("Repositorio: %s", entities))
    print("Avanzar")

    if (is_top(pos_y)) then
        return next_position["reverse"]
    end

    for i = getStart(pos_x), getEnd(pos_x) do
        if (check_position(map[pos_x + i][y + 1])) then
            return next_position[i]
        end
    end

    -- si todos son false avanzar aunque choque
    return "F"
end