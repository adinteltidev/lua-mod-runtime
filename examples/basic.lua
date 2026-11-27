local scores = {7, 4, 10}
table.sort(scores)
assert(table.concat(scores, ",") == "4,7,10")
assert(math.max(table.unpack(scores)) == 10)
assert(io == nil and os == nil and package == nil)
