extends CharacterBody2D

@export var movement_speed: float = 200.0
@export var health: int = 10
@export var movement_target: Node2D

@onready var navigation_agent: NavigationAgent2D = $NavigationAgent2D

func _ready():
	$AnimatedSprite2D.play("idle")
	
	navigation_agent.path_desired_distance = 4.0
	navigation_agent.target_desired_distance = 4.0
	
	call_deferred("actor_setup")
	
func actor_setup():
	await get_tree().physics_frame
	
	#set_movement_target(movement_target.position)

func set_movement_target(target_point: Vector2):
	navigation_agent.target_position = target_point

func _physics_process(delta):
	if navigation_agent.is_navigation_finished():
		return
		
	var current_agent_position: Vector2 = global_position
	var next_path_position: Vector2 = navigation_agent.get_next_path_position()
	
	velocity = current_agent_position.direction_to(next_path_position) * movement_speed
	move_and_slide()


#func _on_visible_on_screen_notifier_2d_screen_exited():
	#queue_free() # Replace with function body.
