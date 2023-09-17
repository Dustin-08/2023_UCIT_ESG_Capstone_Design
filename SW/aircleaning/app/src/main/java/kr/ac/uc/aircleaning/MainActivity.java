package kr.ac.uc.aircleaning;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    ImageView face;

    TextView value,result;
    Button btnRestr;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        face = findViewById(R.id.face);
        value = findViewById(R.id.value);
        result = findViewById(R.id.result);
        btnRestr = findViewById(R.id.btnRestr);

        btnRestr.setOnClickListener(view -> {
            //value 값을 받으면 value 값에 따라 face와 result값이 변하도록
            int numValue = Integer.parseInt(String.valueOf(value));

            if(numValue<=30 && numValue>=0){
                result.setText(getString(R.string.angel));
                face.setImageResource(R.drawable.angel);
            }else if(numValue<=80 && numValue>=31){
                result.setText(getString(R.string.smile));
                face.setImageResource(R.drawable.smile);
            }else if(numValue<=150 && numValue>=81){
                result.setText(getString(R.string.sad));
                face.setImageResource(R.drawable.sad);
            }else if(numValue>=151){
                result.setText(getString(R.string.angry));
                face.setImageResource(R.drawable.angry);
            }
        });
    }
}