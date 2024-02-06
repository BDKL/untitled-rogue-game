extends Node

@export var mob_scene: PackedScene


# Called when the node enters the scene tree for the first time.
func _ready():
	$SpawnTimer.start()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass



func _on_spawn_timer_timeout():
	pass # Replace with function body.
