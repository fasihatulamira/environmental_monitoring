<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Environmental Monitoring System</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
    <div class="container">
        <h1>Environmental Monitoring System</h1>
        <div style="text-align: center; margin-bottom: 20px;">
            <button class="btn" onclick="window.location.reload();">Refresh Data</button>
        </div>
        
        <?php
		include_once('test_data.php');
        // Display data from database
        if (mysqli_num_rows($result) > 0) {
            echo "<table>";
            echo "<tr><th>Timestamp</th><th>ID</th><th>Temperature (°C)</th><th>Humidity (%)</th><th>Distance (cm)</th></tr>";

            while ($row = mysqli_fetch_assoc($result)) {
                echo "<tr>";
                echo "<td>" . $row['timestamp'] . "</td>";
                echo "<td>" . $row['id'] . "</td>";
                echo "<td>" . $row['temperature'] . "</td>";
                echo "<td>" . $row['humidity'] . "</td>";
                echo "<td>" . $row['distance'] . "</td>";
                echo "</tr>";
            }

            echo "</table>";
        } else {
            echo "<p>No data found</p>";
        }
        ?>

    </div>
</body>
</html>