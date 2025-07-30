@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

ECHO Setting up virtual environment...
python -m venv %~dp0.venv > NUL 2> NUL

IF NOT EXIST "%~dp0.venv\Scripts\activate.bat" (
    ECHO Failed to create virtual environment.
    EXIT /B 1
)

ECHO Activating virtual environment...
CALL "%~dp0.venv\Scripts\activate.bat"
IF ERRORLEVEL 1 (
    ECHO Failed to activate virtual environment.
    EXIT /B 1
)

ECHO Installing dependencies...
%~dp0.venv\Scripts\python.exe -m pip install pytest pytest-cov > NUL 2> NUL
IF ERRORLEVEL 1 (
    ECHO Failed to install dependencies.
    EXIT /B 1
)

CALL %~dp0.venv\Scripts\deactivate.bat
ECHO Setup complete.