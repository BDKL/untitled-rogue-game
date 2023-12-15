extends Area2D


# Called when the node enters the scene tree for the first time.
var p1 = Player.new()

func _ready():
	print("calling check_movement")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	p1.check_movement()
