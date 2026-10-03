CREATE DATABASE student_management_system;

USE student_management_system;

-- Departments table
CREATE TABLE Departments (
    department_id INT PRIMARY KEY,
    department_name VARCHAR(100) NOT NULL,
    department_code VARCHAR(20) UNIQUE
);

-- Courses table
CREATE TABLE Courses (
    course_id VARCHAR(20) PRIMARY KEY,
    course_name VARCHAR(50) NOT NULL,
    course_code VARCHAR(20) UNIQUE NOT NULL,
    department_id INT NOT NULL,
    semester INT NOT NULL,
    credits INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (department_id)
        REFERENCES Departments(department_id)
);

-- Sample departments
INSERT INTO Departments
(department_id, department_name, department_code)
VALUES
(1, 'Computer Science', 'CSE'),
(2, 'Physics', 'PHY'),
(3, 'Mathematics', 'MAT');
