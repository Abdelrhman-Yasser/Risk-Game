import unittest
import os
from utilities.IoHandler import IOHandler


class MyTestCase(unittest.TestCase):
    def test_1(self):
        lines = IOHandler.read_file(os.getcwd() + "/read_test")
        self.assertEqual(len(lines), 2)
        self.assertEqual(lines[0], 'read successful 1')
        self.assertEqual(lines[1], 'read successful 2')


if __name__ == '__main__':
    unittest.main()
