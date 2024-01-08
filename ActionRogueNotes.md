



##  **UMG & (player) Attributes**

- Property binding creates a function that runs every frame.  Another way is to register event that notifies UI:  progress widget blueprint binds to OnHealthChange event, and set progress whenever it receives the event. The Design pattern says only UI should listen to the gameplay, not the other way around.

- UI widget can hold to an animation.

- Another simple use case of attribute component is to call apply health when there is a barrel <-> player collision event.



## Dynamic Material

- Material Instance can be created as a child class of material. It only allows tweaking of exposed material parameters buts shows immediate changes in the scene.
- Hit flash logic:  actor owns a mesh comp and an attribute comp. Define a function OnHealthChanged to set material parameters. Register that function to event of attribute comp OnhealthChanged.
- Dissolve material logic:  noise texture + dissolve parameter connects to opacity in mask blend node.



## AI & Behavior Tree

- There are three assets required to run AI behavior: AI controller, Behavior Tree and Blackboard. AI controller manages the AI runtime system, Behavior tree determines character logic and Blackboard holds some form of memory the BT can reference to.
- AI controller holds reference to a behavior tree and Behavior tree references a Blackboard. AI controller has direct access to Blackboard Component.

- To implement a Bot movement behavior, besides above three assets, a Nav Mesh volume that determines bots' movement range needs to be placed in the scene.
- Behavior Tree
  - It is a form of reactive planning that allows you to try things and fall back to other behaviors if they fail.
  - A path from top to a leaf node of the tree represents a course of action. Algorithmically, behavior tree performs depth first search from left to right.
  - Consist of three type of nodes : condition, action, composite
  - Condition tests some property of game, returns true if test is met and return false otherwise.
  -  Action alters some state of the game : animation, character movement, character state ...
  - Composite tasks manage child tasks, and their behaviors depend on their children.
    - Selector: returns success if one of its children runs successfully, and returns failure if it ran out of children.
    - Sequence: returns failure if one of its children fails, and returns success if it runs out of children.

- Custom BT service
  - Unresolved Symbol BUG: Need to include Module in build.cs
  - BT service updates Blackboard memory (can be used to check condition like attack range)
  - Stop in attack range
  - Line of sight check