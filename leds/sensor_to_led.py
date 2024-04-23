import numpy as np

#return a direction based on vector
def direction(vec, ideal, threshold):
    res = ideal - vec
    #see if vector falls within threshold, if so then "centered"
    if (abs(res[1]) < threshold) and (abs(res[0]) < threshold):
        return "center"

    #if not centered, then calculate the angle to find direction
    ang = np.rad2deg(np.arctan2(res[1], res[0]))

    #can adjust angle ranges to indicate more directions
    #left (135 to 180, and -180 to -135)
    if (ang >= 135 and ang <= 180) or (ang >= -180 and ang <= -135):
        return "left"

    #right (0 to 45, and 0 to -45)
    if (ang >= 0 and ang <= 45) or (ang <= 0 and ang >= -45):
        return "right"

    #forward (45 to 135)
    if (ang >= 45 and ang <= 135):
        return "forward"

    #backwards (-135 to -45)
    if (ang <= 45 and ang >= -135):
        return "backward"

#ideal
ideal = np.array([0.0,0.0])

#same direction but different magnitude (should both return left)
t1 = np.array([1,1])
t2 = np.array([0.5,0.5])

#leaning backward (should return forward)
t3 = np.array([-0.5, -0.8])

#leaning forward (should return backward)
t4 = np.array([-0.23, 0.8])

#leaning left (should return right)
t5 = np.array([-0.7, 0.22])

#leaning right (should return left)
t6 = np.array([0.8, -0.25])

#centered (should return centered)
t7 = np.array([0.02, -0.09])

#not centered (should return forward)
t8 = np.array([0.3, -0.5])

#get direction to lean in
dir1 = direction(t1, ideal, 0.1)
dir2 = direction(t2, ideal, 0.1)
dir3 = direction(t3, ideal, 0.1)
dir4 = direction(t4, ideal, 0.1)
dir5 = direction(t5, ideal, 0.1)
dir6 = direction(t6, ideal, 0.1)
dir7 = direction(t7, ideal, 0.1)
dir8 = direction(t8, ideal, 0.1)

print(dir1)
print(dir2)
print(dir3)
print(dir4)
print(dir5)
print(dir6)
print(dir7)
print(dir8)



