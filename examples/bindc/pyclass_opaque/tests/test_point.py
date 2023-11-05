import pytest

from point import Point

def test_point():
    p = Point(1, 2)
    assert p.x == 1
    assert p.y == 2
    assert p != Point(1, 2)

def test_point_euclid():
    p = Point(1, 2)
    p2 = Point(2, 5)
    assert p.euclidean_distance(p2) == 3.1622776601683795

# Test type failure
# This shouldn't segfault
def test_fails():
    p = Point(1, 2)
    with pytest.raises(Exception) as e_info:
        p.euclidean_distance(1)
