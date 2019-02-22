import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Slider;
import javafx.stage.Stage;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.layout.Pane;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;

public class Exercice1 extends Application {
    
    public void start(Stage stage) {
        Slider     rouge   = new Slider(0, 255, 0);
        Slider     vert    = new Slider(0, 255, 0);
        Slider     bleu    = new Slider(0, 255, 0);
	VBox       vbox    = new VBox();
	BorderPane root    = new BorderPane();
	Scene      scene   = new Scene(root, 500, 500);
	Couleur    couleur = new Couleur();

	Pane            pane = new Pane();
	Canvas          rect = new Canvas(450, 450);
	GraphicsContext gc   = rect.getGraphicsContext2D();

	pane.getChildren().add(rect);
	vbox.getChildren().addAll(rouge, vert, bleu);

	rouge.setBlockIncrement(1);
	bleu.setBlockIncrement(1);
	vert.setBlockIncrement(1);

	gc.setFill(Color.BLACK);
	gc.fillRect(0, 0, 450, 450);
	root.setCenter(pane);
	root.setBottom(vbox);

	rouge.valueProperty().addListener(
					  new MonEcouteurCouleur("rouge", rect, couleur));
	bleu.valueProperty().addListener(
					  new MonEcouteurCouleur("bleu", rect, couleur));
	vert.valueProperty().addListener(
					  new MonEcouteurCouleur("vert", rect, couleur));
	pane.widthProperty().addListener(
					 new MonEcouteurTaille("largeur", rect, couleur));
	pane.heightProperty().addListener(
					  new MonEcouteurTaille("hauteur", rect, couleur));

	
        stage.setTitle("Exercice 1");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}


class MonEcouteurCouleur implements ChangeListener<Number> {
    String    base;
    Canvas    rect;
    Couleur   couleur;
    GraphicsContext gc;

    MonEcouteurCouleur (String base, Canvas rect, Couleur couleur) {
	this.base    = base;
	this.rect    = rect;
	this.couleur = couleur;
	gc           = rect.getGraphicsContext2D();
    }
    public void changed(ObservableValue<? extends Number> value,Number oldvalue,Number newvalue){
	if(base.equals("rouge")){
	    couleur.r = newvalue.intValue();
	}else if(base.equals("vert")){
	    couleur.v = newvalue.intValue();
	}else {
	    couleur.b = newvalue.intValue();
	}
	gc.setFill(new Color(couleur.r/255.0, couleur.v/255.0, couleur.b/255.0, 1.0));
	gc.fillRect(0, 0, 450, 450);
    }
}

class MonEcouteurTaille implements ChangeListener<Number> {
    String la_ha;
    Canvas rect;
    Couleur couleur;
    GraphicsContext gc;

    MonEcouteurTaille (String largeur_hauteur, Canvas rect, Couleur couleur) {
	this.la_ha           = la_ha;
	this.rect            = rect;
	this.couleur         = couleur;
	gc                   = rect.getGraphicsContext2D();
    }

    public void changed(ObservableValue<? extends Number> value,Number oldvalue,Number newvalue){

	if(la_ha.equals("largeur")) {
	    rect.setWidth(newvalue.doubleValue());
	} else {
	    rect.setHeight(newvalue.doubleValue());
	}
	gc.setFill(
	  new Color(couleur.r/255.0, couleur.v/255.0, couleur.b/255.0, 1.0));
	gc.fillRect(0, 0, rect.getWidth(), rect.getHeight());
    }
}

class Couleur {
    int r, v, b;

    Couleur () {
	r = v = b = 0;
    }
}
