job("Disk Space Check") {
    steps {
        shell("df")
    }
}

job("Daily Dose of Satisfaction") {
    parameters {
        stringParam("NAME")
    }
    steps {
        shell("echo \"Hello dear \$NAME!\"")
        shell("date")
        shell("echo \"This is your DDoS number \$BUILD_NUMBER.\"")
    }
}
