import java.io.File;
import java.io.IOException;
import java.util.Scanner;

class Main {

    public static int currentCharIndex;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No file name given");
            System.exit(0);
        }
        File in = new File(args[0]);
        try (Scanner scan = new Scanner(in))
        {
            while (scan.hasNext()) {
                currentCharIndex = -1;
                String line = scan.next();
                line += '\0';
                if (A(line)) {
                    System.out.println("The string \"" + line + "\" is in the language");
                } else {
                    System.out.println("The string \"" + line + "\" is not in the language");
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        }

    }

    public static void getNextChar(String line) {
        int max = line.length();
        if (currentCharIndex < max-1) {
            currentCharIndex++;
        }
    }

    public static void putBackChar() {
        if (!(currentCharIndex < 0)) {
            currentCharIndex--;
        }
    }

    public static boolean O(String line) {
        getNextChar(line);
        char c = line.charAt(currentCharIndex);
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (c == '*') {
                getNextChar(line);
                c = line.charAt(currentCharIndex);
                if (c == '*') {
                    return true;
                }
                putBackChar();
                return true;
            }
            return true;
        }
        putBackChar();
        return false;
    }

    public static boolean U(String line) {
        String unary = "+-!";
        getNextChar(line);
        char c = line.charAt(currentCharIndex);
        String temp = Character.toString(c);
        if (unary.contains(temp)) {
            return true;
        }
        putBackChar();
        return false;
    }

    public static boolean D(String line) {
        String digits = "0123456789";
        getNextChar(line);
        char c = line.charAt(currentCharIndex);
        String temp = Character.toString(c);
        if (digits.contains(temp)) {
            return true;
        }
        putBackChar();
        return false;
    }

    public static boolean L(String line) {
        if (D(line)) {
            if (L(line)) {
                return true;
            }
            return true;
        }
        return false;
    }

    public static boolean C(String line) {
        String alphabet = "abcdefghijklmnopqrstuvwxyz";
        getNextChar(line);
        char c = line.charAt(currentCharIndex);
        String temp = Character.toString(c);
        if (alphabet.contains(temp)) {
            return true;
        }
        putBackChar();
        return false;
    }

    public static boolean I(String line) {
        if (C(line)) {
            if (I(line)) {
                return true;
            }
            return true;
        }
        return false;
    }

    public static boolean E(String line) {
        if (P(line)) {
            if (O(line)) {
                return P(line);
            }
            return true;
        }
        return false;
    }

    public static boolean P(String line) {
        if (I(line)) {
            return true;
        }
        if (L(line)) {
            return true;
        }
        if (U(line)) {
            if (I(line)) {
                return true;
            } else if (L(line)) {
                return true;
            }
        }
        getNextChar(line);
        char c = line.charAt(currentCharIndex);
        if (c == '(') {
            if (E(line)) {
                getNextChar(line);
                c = line.charAt(currentCharIndex);
                if (c == ')') {
                    return true;
                }
                putBackChar();
            }
        }
        putBackChar();
        return false;
    }

    public static boolean A(String line) {
        if (I(line)) {
            getNextChar(line);
            char c = line.charAt(currentCharIndex);
            if (c == '=') {
                if (E(line)) {
                    return true;
                }
            }
            putBackChar();
        }
        return false;
    }
}
