<?php
// Database connection parameters
$hostname = "localhost";
$username = "root";
$password = "";
$database = "env_monitor";

// Attempt to connect to the database
$conn = mysqli_connect($hostname, $username, $password, $database);

// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// Check if POST data is received
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Validate and sanitize input data
    $t = isset($_POST["temperature"]) ? mysqli_real_escape_string($conn, $_POST["temperature"]) : null;
    $h = isset($_POST["humidity"]) ? mysqli_real_escape_string($conn, $_POST["humidity"]) : null;
    $distance = isset($_POST["distance"]) ? mysqli_real_escape_string($conn, $_POST["distance"]) : null;

    if ($t !== null && $h !== null && $distance !== null) {
        // Insert data into database
        $sql = "INSERT INTO sensor_data (temperature, humidity, distance) VALUES ('$t', '$h', '$distance')";

        if (mysqli_query($conn, $sql)) {
            echo "New record created successfully";
        } else {
            echo "Error: " . $sql . "<br>" . mysqli_error($conn);
        }
    } else {
        echo "Temperature, humidity, or Sonar distance not set";
    }
}

// Retrieve all data from database
$sql = "SELECT * FROM sensor_data ORDER BY timestamp DESC"; // Select all records, ordered by timestamp descending
$result = mysqli_query($conn, $sql);

// Close database connection
mysqli_close($conn);
?>



