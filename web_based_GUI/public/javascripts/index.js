$(document).ready(function(){
        // Initially set pod-status in local storage to safe to approach.
        localStorage.setItem('pod-status', 2);
});

// Set pod-status in local storage according to button press:
$('#emerg-stop').click(function(){
        localStorage.setItem('pod-status', 0);
});

$('#ready-launch').click(function(){
        localStorage.setItem('pod-status', 1);
});

$('#safe-approach').click(function(){
        localStorage.setItem('pod-status', 2);
});

// Set an event that polls the local storage for pod-status and calls to the back-end to transmit the appropriate status to the pod.
setInterval(function(){
        $.post('/send-status', {status: localStorage.getItem('pod-status')});
}, 1000);