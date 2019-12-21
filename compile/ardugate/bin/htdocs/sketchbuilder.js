var isIE = navigator.userAgent.toLowerCase().indexOf("msie") > -1;
var isMoz = document.implementation && document.implementation.createDocument;
var xmlhttp = newHttpRequest();

function newHttpRequest()
{
	var _xmlhttp;
	if (window.XMLHttpRequest)
	  {// code for all new browsers
	  _xmlhttp=new XMLHttpRequest();
	  }
	else if (window.ActiveXObject)
	  {// code for IE5 and IE6
	  _xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	  }
	 else
	  {
	  alert("Your browser does not support XMLHTTP.");
	  }
	  return _xmlhttp;
}

var mcu = new Array("atmega328p", "atmega328p", "atmega168", "atmega328p", "atmega168", "atmega328p", "atmega168", "atmega328p", "atmega168p", "atmega2560", "atmega1280");
var baudrates = new Array(115200, 57600, 19200, 57600, 19200, 57600, 19200, 57600, 19200, 57600, 57600);
 
function Update()
{
	var index = parseInt(document.getElementById("board").value) - 1;
	/*
	var cmd = "avrdude -C /etc/avrdude.conf -V -p" + mcu[index] + " -carduino -b" + baudrates[index] + " -P[SERIAL_PORT] -D -Uflash:w:[HEX_FILE_PATH]:i";
	document.getElementById("cmdline").value = cmd;
	*/
	document.getElementById("boardInfo").innerHTML = "Board Type: (used for " + stats_board_used[index] + " times)";
	document.getElementById("baudrate").value = baudrates[index];
	document.getElementById("mcu").value = mcu[index];
}

function BuildSketchToHex(sketchContent, boardIndex)
{
	var xmlhttp = newHttpRequest();
	xmlhttp.open("POST", "build.hex?board=" + boardIndex, false);
	xmlhttp.send(sketchContent);
	return xmlhttp.responseText;
}

function BuildUpload()
{
	editor.save()
	var sketch = document.getElementById("code").value;
	var board = document.getElementById("board").value;
	var hex = BuildSketchToHex(sketch, board);
	if (hex.substr(0, 1) == ":") {
		document.getElementById("hex").value = hex;
		alert("Your sketch has been successfully built!\n\nTo upload it to Arduino, please:\n1. connect your Arduino board to your computer\n2. make sure the serial port is correctly specified\n3. make sure AVRDUDE Deamon is running\n\nClick OK to start uploading.");
		document.getElementById("uploadfrm").submit();
	} else {
		alert(hex);	
	}

}

Update();

document.getElementById("ver").innerHTML = "<strong>Version " + builder_ver + "</strong>";
document.getElementById("stats").innerHTML = "<strong>This service has been up running for " + Math.ceil(stats_uptime / 60) + "  minutes with " + stats_total_builds + " builds performed.</strong>";
