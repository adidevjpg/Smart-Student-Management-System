public class Student {

    private int studentId;
    private String rollNo;
    private String firstName;
    private String lastName;
    private String email;
    private String phone;
    private int departmentId;
    private int semester;

    public Student(int studentId, String rollNo, String firstName,
                   String lastName, String email, String phone,
                   int departmentId, int semester) {

        this.studentId = studentId;
        this.rollNo = rollNo;
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.phone = phone;
        this.departmentId = departmentId;
        this.semester = semester;
    }

    public int getStudentId() {
        return studentId;
    }

    public String getRollNo() {
        return rollNo;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getEmail() {
        return email;
    }

    public String getPhone() {
        return phone;
    }

    public int getDepartmentId() {
        return departmentId;
    }

    public int getSemester() {
        return semester;
    }
}
