import subprocess
from pathlib import Path
from bs4 import BeautifulSoup


def highlight_code(code, language):
    """
    Highlight code using tree-sitter and extract CSS styles
    Returns a tuple of (highlighted_html, style_content)
    """
    if language == "moonbit":
        language = "mbt"
    if language == "nil":
        return code, ""

    try:
        proc = subprocess.run(
            [
                "tree-sitter",
                "highlight",
                "--html",
                "--css-classes",
                "--scope",
                f"source.{language}",
            ],
            input=code,
            capture_output=True,
            text=True,
            check=True,
        )

        # Parse the tree-sitter output using BeautifulSoup
        soup = BeautifulSoup("<pre>" + proc.stdout + "</pre>", "html.parser")

        # Extract styles
        style_tags = soup.find_all("style")
        style_content = "\n".join(tag.string for tag in style_tags if tag.string)

        # Extract table content (highlighted code)
        table = soup.find("table")
        table_content = table if table else code

        # Return the highlighted code and style content
        return table_content, style_content
    except subprocess.CalledProcessError:
        # If tree-sitter fails, return the original code
        return code, ""


def main():
    # Read the HTML file
    html_path = Path("src") / "index.html"
    html_content = html_path.read_text()

    # Parse the HTML using BeautifulSoup
    soup = BeautifulSoup(html_content, "html.parser")

    # Collect all tree-sitter styles
    all_styles: str = ""

    # Find all pre tags with class 'src'
    for pre_tag in soup.find_all("pre", class_=lambda c: c and "src" in c.split()):
        # Extract the language from the class
        classes = pre_tag.get("class", [])
        language = None
        for class_name in classes:
            if class_name.startswith("src-"):
                language = class_name[4:]
                break

        if language:
            # Get the code content
            code = pre_tag.get_text().strip()

            # Highlight the code
            highlighted_html, style_content = highlight_code(code, language)

            # Collect styles
            if style_content and not all_styles:
                all_styles = style_content

            # Clear the pre tag content
            pre_tag.clear()

            pre_tag.append(highlighted_html)

    # Inject collected styles into the head
    if all_styles:
        # Create a new style tag
        style_tag = soup.new_tag("style", type="text/css")
        style_tag.string = f"""/* Tree-sitter syntax highlighting styles */
{all_styles}
.comment {{ color: #3a7a3a; }}
"""

        # Add it to the head
        head = soup.find("head")
        if head:
            head.append(style_tag)

    # Create dist directory if it doesn't exist
    dist_dir = Path("dist")
    dist_dir.mkdir(exist_ok=True)

    # Write the modified HTML to the output file
    (dist_dir / "index.html").write_text(str(soup))


if __name__ == "__main__":
    main()
