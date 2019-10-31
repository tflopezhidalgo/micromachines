
next_position = {
    [0] = "R",
    [1] = "F",
    [2] = "L"
}

function check_position(position)
    return entities[position]["safe"]
end

function getAction(pos_x, pos_y)
    print("Avanzar")
    car_pos = map[pos_x, pos_y]
    next_pos = 4
    for i in range(3)
        if (check_position(map[i][y + 1]))
            return next_position[i]
            break
        end
    end
    if (next_pos == 4)
        return "B"
    end
    return 'F'
end