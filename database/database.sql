CREATE DATABASE IF NOT EXISTS smart_student_academic_db;

USE smart_student_academic_db;

CREATE TABLE Users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password_hash VARCHAR(255) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    role ENUM('STUDENT', 'FACULTY', 'ADMIN') NOT NULL,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE Departments (
    department_id INT AUTO_INCREMENT PRIMARY KEY,
    department_code VARCHAR(20) NOT NULL UNIQUE,
    department_name VARCHAR(100) NOT NULL UNIQUE,
    hod_faculty_id INT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Students (
    student_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL UNIQUE,
    roll_number VARCHAR(30) NOT NULL UNIQUE,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50),
    date_of_birth DATE,
    gender VARCHAR(20),
    phone VARCHAR(20),
    address VARCHAR(255),
    department_id INT NOT NULL,
    admission_year YEAR NOT NULL,
    semester INT NOT NULL,
    section VARCHAR(10),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_student_user
        FOREIGN KEY (user_id)
        REFERENCES Users(user_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT fk_student_department
        FOREIGN KEY (department_id)
        REFERENCES Departments(department_id)
        ON DELETE RESTRICT
        ON UPDATE CASCADE,

    CONSTRAINT chk_student_semester
        CHECK (semester BETWEEN 1 AND 8)
);

CREATE TABLE Faculty (
    faculty_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL UNIQUE,
    employee_id VARCHAR(30) NOT NULL UNIQUE,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50),
    phone VARCHAR(20),
    designation VARCHAR(50),
    department_id INT NOT NULL,
    joining_date DATE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_faculty_user
        FOREIGN KEY (user_id)
        REFERENCES Users(user_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT fk_faculty_department
        FOREIGN KEY (department_id)
        REFERENCES Departments(department_id)
        ON DELETE RESTRICT
        ON UPDATE CASCADE
);

ALTER TABLE Departments
ADD CONSTRAINT fk_department_hod
    FOREIGN KEY (hod_faculty_id)
    REFERENCES Faculty(faculty_id)
    ON DELETE SET NULL
    ON UPDATE CASCADE;

CREATE TABLE Courses (
    course_id INT AUTO_INCREMENT PRIMARY KEY,
    course_code VARCHAR(20) NOT NULL UNIQUE,
    course_name VARCHAR(100) NOT NULL,
    credits INT NOT NULL,
    department_id INT NOT NULL,
    semester INT NOT NULL,
    faculty_id INT NOT NULL,
    academic_year VARCHAR(20) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_course_department
        FOREIGN KEY (department_id)
        REFERENCES Departments(department_id)
        ON DELETE RESTRICT
        ON UPDATE CASCADE,

    CONSTRAINT fk_course_faculty
        FOREIGN KEY (faculty_id)
        REFERENCES Faculty(faculty_id)
        ON DELETE RESTRICT
        ON UPDATE CASCADE,

    CONSTRAINT chk_course_credits
        CHECK (credits BETWEEN 1 AND 10),

    CONSTRAINT chk_course_semester
        CHECK (semester BETWEEN 1 AND 8)
);

CREATE TABLE Student_Courses (
    enrollment_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT NOT NULL,
    course_id INT NOT NULL,
    academic_year VARCHAR(20) NOT NULL,
    semester INT NOT NULL,
    enrollment_date DATE DEFAULT (CURRENT_DATE),

    CONSTRAINT fk_enrollment_student
        FOREIGN KEY (student_id)
        REFERENCES Students(student_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT fk_enrollment_course
        FOREIGN KEY (course_id)
        REFERENCES Courses(course_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT uq_student_course
        UNIQUE (
            student_id,
            course_id,
            academic_year,
            semester
        ),

    CONSTRAINT chk_enrollment_semester
        CHECK (semester BETWEEN 1 AND 8)
);

CREATE TABLE Attendance (
    attendance_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT NOT NULL,
    course_id INT NOT NULL,
    attendance_date DATE NOT NULL,
    status ENUM(
        'PRESENT',
        'ABSENT',
        'LATE',
        'EXCUSED'
    ) NOT NULL,
    remarks VARCHAR(255),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT fk_attendance_student
        FOREIGN KEY (student_id)
        REFERENCES Students(student_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT fk_attendance_course
        FOREIGN KEY (course_id)
        REFERENCES Courses(course_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT uq_student_course_date
        UNIQUE (
            student_id,
            course_id,
            attendance_date
        )
);

CREATE TABLE Marks (
    mark_id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT NOT NULL,
    course_id INT NOT NULL,

    assessment_type ENUM(
        'ASSIGNMENT',
        'QUIZ',
        'MIDTERM',
        'FINAL',
        'PROJECT',
        'PRACTICAL'
    ) NOT NULL,

    marks_obtained DECIMAL(5,2) NOT NULL,
    maximum_marks DECIMAL(5,2) NOT NULL,
    grade VARCHAR(5),
    exam_date DATE,
    remarks VARCHAR(255),

    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        ON UPDATE CURRENT_TIMESTAMP,

    CONSTRAINT fk_marks_student
        FOREIGN KEY (student_id)
        REFERENCES Students(student_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT fk_marks_course
        FOREIGN KEY (course_id)
        REFERENCES Courses(course_id)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT chk_marks_valid
        CHECK (
            marks_obtained >= 0
            AND maximum_marks > 0
            AND marks_obtained <= maximum_marks
        ),

    CONSTRAINT uq_student_course_assessment
        UNIQUE (
            student_id,
            course_id,
            assessment_type
        )
);

CREATE INDEX idx_students_department
ON Students(department_id);

CREATE INDEX idx_students_semester
ON Students(semester);

CREATE INDEX idx_faculty_department
ON Faculty(department_id);

CREATE INDEX idx_courses_department
ON Courses(department_id);

CREATE INDEX idx_courses_faculty
ON Courses(faculty_id);

CREATE INDEX idx_courses_semester
ON Courses(semester);

CREATE INDEX idx_courses_academic_year
ON Courses(academic_year);

CREATE INDEX idx_enrollment_student
ON Student_Courses(student_id);

CREATE INDEX idx_enrollment_course
ON Student_Courses(course_id);

CREATE INDEX idx_enrollment_semester
ON Student_Courses(semester);

CREATE INDEX idx_attendance_student
ON Attendance(student_id);

CREATE INDEX idx_attendance_course
ON Attendance(course_id);

CREATE INDEX idx_attendance_date
ON Attendance(attendance_date);

CREATE INDEX idx_marks_student
ON Marks(student_id);

CREATE INDEX idx_marks_course
ON Marks(course_id);

CREATE INDEX idx_marks_assessment
ON Marks(assessment_type);

CREATE VIEW Student_Attendance_Summary AS
SELECT
    s.student_id,
    s.roll_number,

    CONCAT(
        s.first_name,
        ' ',
        COALESCE(s.last_name, '')
    ) AS student_name,

    c.course_id,
    c.course_code,
    c.course_name,

    COUNT(a.attendance_id) AS total_classes,

    SUM(
        CASE
            WHEN a.status IN ('PRESENT', 'LATE')
            THEN 1
            ELSE 0
        END
    ) AS attended_classes,

    ROUND(
        (
            SUM(
                CASE
                    WHEN a.status IN ('PRESENT', 'LATE')
                    THEN 1
                    ELSE 0
                END
            )
            / NULLIF(COUNT(a.attendance_id), 0)
        ) * 100,
        2
    ) AS attendance_percentage

FROM Students s

JOIN Attendance a
    ON s.student_id = a.student_id

JOIN Courses c
    ON a.course_id = c.course_id

GROUP BY
    s.student_id,
    s.roll_number,
    s.first_name,
    s.last_name,
    c.course_id,
    c.course_code,
    c.course_name;

CREATE VIEW Student_Marks_Summary AS
SELECT
    s.student_id,
    s.roll_number,

    CONCAT(
        s.first_name,
        ' ',
        COALESCE(s.last_name, '')
    ) AS student_name,

    c.course_id,
    c.course_code,
    c.course_name,

    SUM(m.marks_obtained) AS total_marks_obtained,

    SUM(m.maximum_marks) AS total_maximum_marks,

    ROUND(
        (
            SUM(m.marks_obtained)
            / NULLIF(SUM(m.maximum_marks), 0)
        ) * 100,
        2
    ) AS percentage

FROM Students s

JOIN Marks m
    ON s.student_id = m.student_id

JOIN Courses c
    ON m.course_id = c.course_id

GROUP BY
    s.student_id,
    s.roll_number,
    s.first_name,
    s.last_name,
    c.course_id,
    c.course_code,
    c.course_name;