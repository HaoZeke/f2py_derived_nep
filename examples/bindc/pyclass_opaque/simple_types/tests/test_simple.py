import pytest

from point import Point


def test_point():
    p = Point(1, 2)
    assert p.x == 1
    assert p.y == 2
    assert p != Point(1, 2)
