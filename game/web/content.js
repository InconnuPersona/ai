//const canvas

function load_shader() {
	
}

function init() {
	sucess = false;
	
	canvas = document.querySelector("#glCanvas");
	
	gl = canvas.getContext("webgl");
	
	if (gl == null) {
		alert("Unable to get WebGL context. Your client may not support it.");
		return;
	}
	
	
	success = true;
}

function draw() {
	gl.clearColor(0, 0, 0, 1);
	gl.clear(gl.COLOR_BUFFER_BIT);
	
	//
	
}

window.onload(init);
