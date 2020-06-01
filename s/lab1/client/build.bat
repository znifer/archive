@echo off
REM �� �������਩.
REM %�������� ��६�����% - ���饭�� � ��६�����.

REM ---------------------------------------------
REM �� ��६���� ����� � �㦭� ������.
REM ---------------------------------------------
REM project_name - ��� �ᯮ��塞��� 䠩��
REM tc_path - ��᮫��� ���� � ����� � Turbo C++ (ᬮ�� � .conf 䠩��)
REM source_files - ��室�� .c 䠩�� �१ �஡��
REM obj_files - 䠩�� ����� ��������� ��᫥ �������樨, � ���� ᮢ���� � .c 䠩����
REM ---------------------------------------------
set project_name=client
set tc_path=d:\tc
set source_files=ipx.c main.c
set obj_files=ipx_init.obj ipx.obj main.obj

REM ---------------------------------------------
REM �� ��६���� ������ �� �⮨�.
REM ---------------------------------------------
REM tc_bin_path - ���� � ����� bin, Turbo C++
REM tc_lib_path - ���� � ����� lib, Turbo C++
REM tc_inc_path - ���� � ����� include, Turbo C++
REM cxx_flags - 䫠�� �������樨 tcc
REM link_flags - 䫠�� �������� tlink
REM ---------------------------------------------
set tc_bin_path=%tc_path%\bin
set tc_lib_path=%tc_path%\lib
set tc_inc_path=%tc_path%\include
set cxx_flags=-I%tc_bin_path% -c -mt %source_files%
set link_flags=-L%tc_lib_path% %tc_lib_path%\c0t.obj %obj_files%,%project_name%.com,%project_name%.map,cs.lib 

REM ---------------------------------------------
REM �����।�⢥��� �ਯ� ᡮન.
REM ---------------------------------------------

%tc_bin_path%\tcc %cxx_flags% 
%tc_bin_path%\tlink %link_flags% 
echo �� � �ந��諮... 