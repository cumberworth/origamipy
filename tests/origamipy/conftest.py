"""Shared fixtures for testing origamipy"""

import pytest

from origamipy import files

@pytest.fixture
def four_domain_struct_inp_file():
    return files.JSONStructInpFile('tests/data/four_unbound.json')
