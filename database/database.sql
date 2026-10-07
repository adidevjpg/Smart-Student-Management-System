-- ============================================================
-- Smart Student Management System - Complete Database Schema
-- ============================================================

CREATE DATABASE IF NOT EXISTS student_management_system;
USE student_management_system;

-- 1. Departments Table
CREATE TABLE IF NOT EXISTS Departments (
    department_id INT PRIMARY KEY,
    department_name VARCHAR(100) NOT NULL,
    department_code VARCHAR(20) UNIQUE NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- 2. Students Table
CREATE TABLE IF NOT EXISTS Students (
    student_id INT AUTO_INCREMENT PRIMARY KEY,
    roll_no VARCHAR(20) NOT NULL UNIQUE,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50),
    email VARCHAR(100) NOT NULL UNIQUE,
    phone VARCHAR(15),
    department_id INT,
    semester INT,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (department_id) REFERENCES Departments(department_id) ON DELETE SET NULL
);

-- 3. Faculty Table
CREATE TABLE IF NOT EXISTS Faculty (
    faculty_id INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50),
    email VARCHAR(100) NOT NULL UNIQUE,
    phone VARCHAR(15),
    department_id INT,
    designation VARCHAR(100),
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (department_id) REFERENCES Departments(department_id) ON DELETE SET NULL
);

-- 4. Courses Table
CREATE TABLE IF NOT EXISTS Courses (
    course_id VARCHAR(20) PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL,
    course_code VARCHAR(20) UNIQUE NOT NULL,
    department_id INT,
    semester INT NOT NULL,
    credits INT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (department_id) REFERENCES Departments(department_id) ON DELETE SET NULL
);

-- 5. Users Table
CREATE TABLE IF NOT EXISTS Users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    email VARCHAR(100) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    role VARCHAR(20) NOT NULL, -- Admin, Faculty, Student
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- 6. Attendance Table
CREATE TABLE IF NOT EXISTS Attendance (
    attendance_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT NOT NULL,
    course_id VARCHAR(20) NOT NULL,
    attendance_date DATE NOT NULL,
    status VARCHAR(10) NOT NULL, -- Present, Absent
    FOREIGN KEY (student_id) REFERENCES Students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES Courses(course_id) ON DELETE CASCADE
);

-- 7. Marks Table
CREATE TABLE IF NOT EXISTS Marks (
    mark_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT NOT NULL,
    course_id VARCHAR(20) NOT NULL,
    marks_obtained DECIMAL(5,2) NOT NULL,
    exam_type VARCHAR(50) NOT NULL,
    exam_date DATE,
    FOREIGN KEY (student_id) REFERENCES Students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES Courses(course_id) ON DELETE CASCADE
);

-- ============================================================
-- Sample Data Insertion
-- ============================================================

-- Sample Departments
INSERT INTO Departments (department_id, department_name, department_code) VALUES
(1, 'Computer Science and Engineering', 'CSE'),
(2, 'Information Technology', 'IT'),
(3, 'Electronics and Communication', 'ECE')
ON DUPLICATE KEY UPDATE department_name = VALUES(department_name);

-- Sample Users
INSERT INTO Users (user_id, username, email, password, role) VALUES
(1, 'admin', 'admin@college.edu', 'admin123', 'Admin'),
(2, 'student', 'student@college.edu', 'student123', 'Student'),
(3, 'faculty', 'faculty@college.edu', 'faculty123', 'Faculty')
ON DUPLICATE KEY UPDATE username = VALUES(username);

-- Sample Courses
INSERT INTO Courses (course_id, course_name, course_code, department_id, semester, credits) VALUES
('CS101', 'Intro to Programming in C', 'CSE101', 1, 1, 4),
('CS102', 'Data Structures and Algorithms', 'CSE102', 1, 2, 4),
('CS103', 'Database Management Systems', 'CSE103', 1, 3, 3)
ON DUPLICATE KEY UPDATE course_name = VALUES(course_name);

-- Sample Students
INSERT INTO Students (student_id, roll_no, first_name, last_name, email, phone, department_id, semester) VALUES
(101, 'CSE2026001', 'Rahul', 'Sharma', 'rahul@student.edu', '9876543210', 1, 1),
(102, 'CSE2026002', 'Amit', 'Verma', 'amit@student.edu', '9876543211', 1, 1),
(103, 'CSE2026003', 'Priya', 'Singh', 'priya@student.edu', '9876543212', 1, 1)
ON DUPLICATE KEY UPDATE first_name = VALUES(first_name);

-- Sample Faculty
INSERT INTO Faculty (faculty_id, first_name, last_name, email, phone, department_id, designation) VALUES
(1, 'Dr. Sunita', 'Roy', 'sunita.roy@college.edu', '9123456780', 1, 'Professor'),
(2, 'Prof. Arvind', 'Menon', 'arvind.menon@college.edu', '9123456781', 1, 'Associate Professor')
ON DUPLICATE KEY UPDATE first_name = VALUES(first_name);
