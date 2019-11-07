--
-- User: eliana
-- Date: 5/11/19
--

floor_id = {
    [0] = {
        ["name"] = "glass",
        ["safe"] = false
    },
    [1] = {
        ["name"] = "vertical",
        ["safe"] = true,
        ["U"] = 0,
        ["D"] = 0,
        ["R"] = -1,
        ["L"] = 1
    },
    [2] = {
        ["name"] = "horizontal",
        ["safe"] = true,
        ["R"] = 0,
        ["L"] = 0,
        ["U"] = 1,
        ["D"] = -1,
    },
    [3] = {
        ["name"] = "first_quadrant",
        ["safe"] = true,
        ["U"] = 1,
        ["R"] = -1
    },
    [4] = {
        ["name"] = "second_quadrant",
        ["safe"] = true,
        ["L"] = 1,
        ["U"] = -1
    },
    [5] = {
        ["name"] = "third_quadrant",
        ["safe"] = true,
        ["D"] = 1,
        ["L"] = -1
    },
    [6] = {
        ["name"] = "fourth_quadrant",
        ["safe"] = true,
        ["R"] = 1,
        ["D"] = -1
    }
}

